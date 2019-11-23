require 'commander/import'
require 'pathname'



def times_with_progress_bar(n)
    steps = n / 100
    rest = n % 100
    progress_bar = Commander::UI::ProgressBar.new 101

    100.times do
        steps.times do
            yield
        end

        progress_bar.increment
    end

    rest.times do
        yield
    end

    progress_bar.increment
end


module Optimization
    Vertex = Struct.new(:x, :y, :z)

    class Triangle
        def initialize(vertices, p, q, r)
            @p, @q, @r = p, q, r

            @min_x = [ vertices[p].x, vertices[q].x, vertices[r].x ].min
            @max_x = [ vertices[p].x, vertices[q].x, vertices[r].x ].max
            @min_y = [ vertices[p].y, vertices[q].y, vertices[r].y ].min
            @max_y = [ vertices[p].y, vertices[q].y, vertices[r].y ].max
            @min_z = [ vertices[p].z, vertices[q].z, vertices[r].z ].min
            @max_z = [ vertices[p].z, vertices[q].z, vertices[r].z ].max
        end

        attr_reader :min_x, :min_y, :min_z, :max_x, :max_y, :max_z, :p, :q, :r
    end

    class Box
        def initialize(*children)
            @children = children

            @min_x = children.map(&:min_x).min
            @min_y = children.map(&:min_y).min
            @min_z = children.map(&:min_z).min
            @max_x = children.map(&:min_x).max
            @max_y = children.map(&:min_y).max
            @max_z = children.map(&:min_z).max
        end

        attr_reader :min_x, :min_y, :min_z, :max_x, :max_y, :max_z, :children
    end

    def self.optimize(nodes)
        if nodes.size == 1
            nodes[0]
        else
            x_size = nodes.map(&:max_x).max - nodes.map(&:min_x).min
            y_size = nodes.map(&:max_y).max - nodes.map(&:min_y).min
            z_size = nodes.map(&:max_z).max - nodes.map(&:min_z).min

            if x_size >= y_size and x_size >= z_size
                nodes.sort! { |t1, t2| t1.min_x <=> t2.min_x }
            elsif y_size >= x_size and y_size >= z_size
                nodes.sort! { |t1, t2| t1.min_y <=> t2.min_y }
            else
                nodes.sort! { |t1, t2| t1.min_z <=> t2.min_z }
            end

            left_nodes = nodes[0...nodes.size / 2]
            right_nodes = nodes[nodes.size / 2..-1]

            optimized_left = optimize left_nodes
            optimized_right = optimize right_nodes

            Box.new(optimized_left, optimized_right)
        end
    end

    class HierarchyTextWriter
        def initialize(out)
            @out = out
        end

        def write_vertices(vertices)
            @out.puts "#{vertices.size}"

            vertices.each do |vertex|
                @out.puts "#{vertex.x} #{vertex.y} #{vertex.z}"
            end
        end

        def write_hierarchy(root)
            case root
            when Box
                root.children.each do |child|
                    write_hierarchy child
                end

                @out.puts "b #{root.children.size}"

            when Triangle
                @out.puts "t #{root.p} #{root.q} #{root.r}"
            end
        end
    end

    def self.write_hierarchy_to_text_file(out, optimization_result)
        writer = HierarchyTextWriter.new(out)
        writer.write_vertices(optimization_result[:vertices])
        writer.write_hierarchy(optimization_result[:root])
    end
end


# Functions for files with .mesh extension
module MeshExtension
    def self.stats(path)
        File.open(path, 'r') do |file|
            n_vertices = file.gets.to_i
            puts "Number of vertices: #{n_vertices}"

            n_vertices.times do
                file.gets
            end

            n_triangles = file.gets.to_i
            puts "Number of triangles: #{n_triangles}"
        end
    end

    def self.optimize(in_stream)
        n_vertices = in_stream.gets.to_i
        vertices = (1..n_vertices).map { Optimization::Vertex.new(*in_stream.gets.split.map(&:to_f)) }
        n_triangles = in_stream.gets.to_i
        triangles = (1..n_triangles).map { Optimization::Triangle.new(vertices, *in_stream.gets.split.map(&:to_i)) }

        { :root => Optimization.optimize(triangles), :vertices => vertices }
    end
end

# Optimized meshes in text format
module OMeshExtension
    def self.write_hierarchy(out_stream, root)
        Optimization::write_hierarchy_to_text_file out_stream, root
    end
end

$extensions = {
    '.mesh' => MeshExtension,
    '.omesh' => OMeshExtension,
}


program :name, 'Mesh'
program :version, '1.0.0'
program :description, 'Processes meshes'


command :stats do |c|
    c.syntax = 'stats FILE'
    c.description = 'shows statistics of mesh'

    c.action do |args, options|
        abort 'Argument required' unless args.size == 1

        path = Pathname.new args[0]
        extension = path.extname

        $extensions[path.extname].stats path
    end
end

command :optimize do |c|
    c.syntax = 'optimize IN OUT'
    c.description = 'optimizes mesh'

    c.action do |args, options|
        abort 'Two arguments required' unless args.size == 2

        in_path = Pathname.new args[0]
        out_path = Pathname.new args[1]
        extension = in_path.extname

        optimization_result = File.open(in_path, 'r') do |in_stream|
            $extensions[in_path.extname].optimize in_stream
        end

        File.open(out_path, 'w') do |out_stream|
            $extensions[out_path.extname].write_hierarchy out_stream, optimization_result
        end
    end
end
