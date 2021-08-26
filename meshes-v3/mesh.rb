#!/usr/bin/env ruby
# require 'commander/import'
require 'pathname'


XYZ = Struct.new :x, :y, :z

Mesh = Struct.new :vertices, :normals, :contents

Triangle = Struct.new :mesh, :i, :j, :k do
  def vertices
    [i, j, k].map { |index| mesh.vertices[index] }
  end

  def min(coordinate)
    vertices.map(&coordinate).min
  end

  def max(coordinate)
    vertices.map(&coordinate).max
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
        triangle = Triangle.new(mesh, *args.map(&:to_i))
        contents << triangle
      end
    end

    mesh
  end
end

def build_hierarchy(triangles)
  return Box.new(triangles) if triangles.size < 5

  min_x = triangles.map { |t| t.min(:x) }
  min_y = triangles.map { |t| t.min(:y) }
  min_z = triangles.map { |t| t.min(:z) }
  max_x = triangles.map { |t| t.max(:x) }
  max_y = triangles.map { |t| t.max(:y) }
  max_z = triangles.map { |t| t.max(:z) }

  dx = max_x - min_x
  dy = max_y - min_y
  dz = max_z - min_z

  smallest = [dx, dy, dz].min

  case
  when dx == smallest
    split_axis = :x

  when dy == smallest
    split_axis = :y

  else
    split_axis = :z
  end

  triangles.sort_by { |t| t.min(split_axis) }

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
  end
end


def optimize(input_pathname, output_pathname)
  mesh = read_mesh input_pathname
  hierarchy = build_hierarchy(mesh.contents)
  optimized_mesh = Mesh.new(mesh.vertices, mesh.normals, [hierarchy])
  write_mesh(optimized_mesh, output_pathname)
end


optimize(Pathname.new(ARGV[1]), Pathname.new(ARGV[2]))


# program :name, 'Mesh'
# program :version, '3.0.0'
# program :description, 'Processes meshes'


# command :optimize do |c|
#   c.syntax = 'optimize IN OUT'
#   c.description = 'optimizes mesh'

#   c.action do |args, options|
#     abort 'Two arguments required' unless args.size == 2

#     in_path = Pathname.new args[0]
#     out_path = Pathname.new args[1]

#     optimize(in_path, out_path)
#   end
# end
