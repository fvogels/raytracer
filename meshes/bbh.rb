require './shared.rb'
require 'benchmark'


data = load_raw(STDIN)

$vertices = data[:vertices]
$triangles = data[:triangles]


class Leaf
  def initialize(triangle_index)
    @triangle_index = triangle_index
    @bounding_box = $triangles[triangle_index].dereference($vertices).bounding_box
  end

  def triangle
    $triangles[triangle_index]
  end

  attr_reader :bounding_box, :triangle_index
end

class Branch
  def initialize(children)
    @children = children
    @bounding_box = children.map(&:bounding_box).inject(Box.empty, &:merge)
  end

  attr_reader :bounding_box, :children
end


def build_hierarchy(nodes)
  if nodes.size <= 2
  then
    nodes.each do |node|
      abort "Expected Leaf" unless Leaf === node

      triangle = $triangles[node.triangle_index]
      puts "t #{triangle.a} #{triangle.b} #{triangle.c}"
    end

    puts "g" if nodes.size == 2

  else
    min_xs = nodes.map { |node| node.bounding_box.x.min }.min
    max_xs = nodes.map { |node| node.bounding_box.x.max }.max
    min_ys = nodes.map { |node| node.bounding_box.y.min }.min
    max_ys = nodes.map { |node| node.bounding_box.y.max }.max
    min_zs = nodes.map { |node| node.bounding_box.z.min }.min
    max_zs = nodes.map { |node| node.bounding_box.z.max }.max

    dx = max_xs - min_xs
    dy = max_ys - min_ys
    dz = max_zs - min_zs

    longest_dimension = [ [ :x, dx ], [ :y, dy ], [ :z, dz ] ].sort do |x, y|
      -(x[1] <=> y[1])
    end[0][0]

    case longest_dimension
    when :x
    then
      nodes.sort! do |a, b|
        a.bounding_box.x.max <=> b.bounding_box.x.max
      end

    when :y
    then
      nodes.sort! do |a, b|
        a.bounding_box.y.max <=> b.bounding_box.y.max
      end

    when :z
    then
      nodes.sort! do |a, b|
        a.bounding_box.z.max <=> b.bounding_box.z.max
      end
    end

    left_nodes = nodes[0...nodes.size / 2]
    right_nodes = nodes[nodes.size / 2..-1]
    nodes = nil
    left_hierarchy = build_hierarchy(left_nodes)
    right_hierarchy = build_hierarchy(right_nodes)

    puts "g"
  end
end


STDERR.puts(Benchmark.measure do
  puts "bbh"
  write_vertices($vertices)
  build_hierarchy( (0...$triangles.size).map { |i| Leaf.new i } )
  puts "end"
end)
