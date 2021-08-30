require_relative './progress'


module Optimization
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


  def self.read_mesh(pathname)
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

  def self.build_hierarchy(triangles, progress)
    if triangles.size < 5
      progress.step(triangles.size)
      return Box.new(triangles)
    end

    split_axis = [ :x, :y, :z ].max_by do |axis|
      min = triangles.map { |t| t.min(axis) }.min
      max = triangles.map { |t| t.max(axis) }.max
      max - min
    end

    triangles.sort_by! { |t| t.min(split_axis) }

    left = triangles[0...triangles.size / 2]
    right = triangles[triangles.size / 2..-1]

    left_hierarchy = build_hierarchy(left, progress)
    right_hierarchy = build_hierarchy(right, progress)

    Box.new [left_hierarchy, right_hierarchy]
  end


  class MeshWriter
    def initialize(file, mesh)
      @file = file
      @mesh = mesh
    end

    def write
      write_header
      write_vertices
      write_normals
      write_contents
      write_footer
    end

    def write_header
      output "#{@mesh.vertices.size} #{@mesh.normals.size}"
    end

    def write_footer
      output 'end'
    end

    def write_vertices
      @mesh.vertices.each do |vertex|
        output "#{vertex.x} #{vertex.y} #{vertex.z}"
      end
    end

    def write_normals
      @mesh.normals.each do |normal|
        output "#{normal.x} #{normal.y} #{normal.z}"
      end
    end

    def write_contents
      @mesh.contents.each do |hierarchy|
        write_hierarchy(hierarchy)
      end
    end

    def output(string)
      @file.puts string
    end

    def write_hierarchy(hierarchy)
      case hierarchy
      when Box
        write_box hierarchy

      when Triangle
        write_triangle hierarchy

      else
        abort 'Eh?'
      end
    end

    def write_box(box)
      box.children.each do |child|
        write_hierarchy(child)
      end

      output "b #{box.children.size}"
    end

    def write_triangle(triangle)
      output "t #{triangle.i} #{triangle.j} #{triangle.k}"
    end
  end


  def self.write_mesh(mesh, output_pathname)
    output_pathname.open('w') do |file|
      MeshWriter.new(file, mesh).write
    end
  end
end

def optimize(input_pathname, output_pathname)
  mesh = Optimization.read_mesh input_pathname
  hierarchy = Optimization.build_hierarchy(mesh.contents.dup, Progress.new(mesh.contents.size))
  optimized_mesh = Optimization::Mesh.new(mesh.vertices, mesh.normals, [hierarchy])
  Optimization.write_mesh(optimized_mesh, output_pathname)
end
