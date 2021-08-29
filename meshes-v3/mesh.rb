#!/usr/bin/env ruby
require 'commander/import'
require 'pathname'


XYZ = Struct.new :x, :y, :z do
  def to_a
    [x, y, z]
  end
end

Mesh = Struct.new :vertices, :normals, :contents do
  def to_s
    "<Mesh>"
  end

  def inspect
    "<Mesh>"
  end
end

class Triangle
  def initialize(mesh, i, j, k)
    abort "Invalid vertex index #{i}, mesh has #{mesh.vertices.size} vertices}" unless i < mesh.vertices.size
    abort "Invalid vertex index #{j}, mesh has #{mesh.vertices.size} vertices}" unless j < mesh.vertices.size
    abort "Invalid vertex index #{k}, mesh has #{mesh.vertices.size} vertices}" unless k < mesh.vertices.size

    @i = i
    @j = j
    @k = k

    @vertices = [i, j, k].map { |index| mesh.vertices[index] }
    @min = Hash[[:x, :y, :z].map { |coordinate| [coordinate, @vertices.map(&coordinate).min ] }]
    @max = Hash[[:x, :y, :z].map { |coordinate| [coordinate, @vertices.map(&coordinate).max ] }]
  end

  attr_reader :mesh, :i, :j, :k, :vertices

  def indices
    [i, j, k]
  end

  def min(coordinate)
    @min[coordinate]
  end

  def max(coordinate)
    @max[coordinate]
  end
end

Box = Struct.new :children


def read_mesh(pathname)
  pathname.open do |file|
    n_vertices, n_normals = file.readline.strip.split.map(&:to_i)
    vertices = (1..n_vertices).map { XYZ.new(*file.readline.split.map(&:to_f)) }
    normals = (1..n_normals).map { XYZ.new(*file.readline.split.map(&:to_f)) }
    contents = []
    mesh = Mesh.new vertices, normals, contents

    while (line = file.readline.strip) != 'end'
      label, *args = line.strip.split

      if label == 't'
        abort "Expected 3 arguments for triangle" unless args.size == 3

        triangle = Triangle.new(mesh, *args.map(&:to_i))
        contents << triangle
      end
    end

    mesh
  end
end

def build_hierarchy(triangles)
  return triangles[0] if triangles.size == 1
  return Box.new(triangles) if triangles.size < 5

  split_axis = [ :x, :y, :z ].max_by do |axis|
    min = triangles.map { |t| t.min(axis) }.min
    max = triangles.map { |t| t.max(axis) }.max
    max - min
  end

  triangles.sort_by! { |t| t.min(split_axis) }

  left = triangles[0...triangles.size / 2]
  right = triangles[triangles.size / 2..-1]

  left_hierarchy = build_hierarchy(left)
  right_hierarchy = build_hierarchy(right)

  Box.new [left_hierarchy, right_hierarchy]
end

def write_hierarchy(hierarchy, file)
  case hierarchy
  when Box
    box = hierarchy
    box.children.each do |child|
      write_hierarchy(child, file)
    end
    file.puts "b #{box.children.size}"

  when Triangle
    triangle = hierarchy
    file.puts "t #{triangle.i} #{triangle.j} #{triangle.k}"

  else
    abort 'Eh?'
  end
end

def write_mesh(mesh, output_pathname)
  output_pathname.open('w') do |file|
    file.puts "#{mesh.vertices.size} #{mesh.normals.size}"
    mesh.vertices.each do |vertex|
      file.puts "#{vertex.x} #{vertex.y} #{vertex.z}"
    end
    mesh.normals.each do |normal|
      file.puts "#{normal.x} #{normal.y} #{normal.z}"
    end
    mesh.contents.each do |hierarchy|
      write_hierarchy(hierarchy, file)
    end
    file.puts 'end'
  end
end


def optimize(input_pathname, output_pathname)
  mesh = read_mesh input_pathname
  hierarchy = build_hierarchy(mesh.contents.dup)
  optimized_mesh = Mesh.new(mesh.vertices, mesh.normals, [hierarchy])
  write_mesh(optimized_mesh, output_pathname)
end



def convert_to_binary(input_pathname, output_pathname)
  input_pathname.open('r') do |input|
    output_pathname.open('wb') do |file|
      n_vertices, n_normals = input.gets.strip.split.map(&:to_i)
      file.write([ n_vertices, n_normals ].pack('II'))

      n_vertices.times do
        vertex = input.gets.split.map(&:to_f)
        file.write(vertex.pack('DDD'))
      end

      n_normals.times do
        normal = input.gets.split.map(&:to_f)
        file.write(normal.pack('DDD'))
      end

      while (line = input.gets.strip) != 'end'
        tag, *args = line.split

        case tag
        when 'b'
          n_children = args[0].to_i
          file.write([0, n_children].pack('II'))

        when 't'
          vertex_indices = args.map(&:to_i)
          file.write([1, *vertex_indices].pack('IIII'))
        end
      end

      file.write([0xFFFFFFFF].pack('I'))
    end
  end
end


# class TriangleVertex
#   def initialize(v, vt=nil, vn=nil)
#     @v = v
#     @vt = vt
#     @vn = vn
#   end

#   attr_reader :v, :vt, :vn
# end

def convert_obj_to_mesh(input_pathname, output_pathname)
  vertices = []
  normals = []
  triangles = []

  input_pathname.open do |input|
    input.each_line do |line|
      tag, *args = line.strip.split

      case tag
      when 'v'
        vertices << args
      when 'f'
        case args.size
        when 3
          triangles_vertices = [ args ]
        else
          abort "face with #{args.size} vertices found!" if args.size != 3
        end

        triangles_vertices.each do |triangle_vertices|
          abort "No support for v/vt/vn in faces" unless triangle_vertices.all? { |v| /^\d+$/ =~ v }

          triangles << triangle_vertices
        end
      when 'vn'
        normals << args
      when 'vt'
        # ignore
      else
        abort "Unsupported tag #{tag}"
      end
    end
  end

  # Remove this to add support for normals
  normals = []

  output_pathname.open('w') do |output|
    output.puts("#{vertices.size} #{normals.size}")

    vertices.each { |vertex| output.puts vertex.join(' ') }
    normals.each { |normal| output.puts normal.join(' ') }

    triangles.each do |triangle|
      indices = triangle.map { |v| v.to_i - 1 }
      output.puts "t #{indices.join(' ')}"
    end

    output.puts "b #{triangles.size}"
    output.puts "end"
  end
end


program :name, 'Mesh'
program :version, '3.0.0'
program :description, 'Processes meshes'


command :optimize do |c|
  c.syntax = 'optimize IN OUT'
  c.description = 'optimizes mesh'

  c.action do |args, options|
    abort 'Two arguments required' unless args.size == 2

    in_path = Pathname.new args[0]
    out_path = Pathname.new args[1]

    optimize(in_path, out_path)
  end
end

command :binary do |c|
  c.syntax = 'binary IN OUT'
  c.description = 'makes binary version'

  c.action do |args, options|
    abort 'Two arguments required' unless args.size == 2

    in_path = Pathname.new args[0]
    out_path = Pathname.new args[1]

    convert_to_binary(in_path, out_path)
  end
end

command :obj2mesh do |c|
  c.syntax = 'obj2mesh IN OUT'
  c.description = 'converts .obj to .mesh'

  c.action do |args, options|
    abort 'Two arguments required' unless args.size == 2

    in_path = Pathname.new args[0]
    out_path = Pathname.new args[1]

    convert_obj_to_mesh(in_path, out_path)
  end
end

