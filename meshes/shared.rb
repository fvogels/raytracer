Vertex = Struct.new(:x, :y, :z)

Triangle = Struct.new(:a, :b, :c) do
  def vertices
    [ a, b, c ]
  end

  def dereference(vertices)
    Triangle.new( vertices[a], vertices[b], vertices[c] )
  end

  def bounding_box
    xs = vertices.map(&:x)
    ys = vertices.map(&:y)
    zs = vertices.map(&:z)

    Box.new( Interval.encompassing(xs), Interval.encompassing(ys), Interval.encompassing(zs) )
  end
end


class Interval
  def initialize(min, max)
    @min, @max = min, max
  end

  def self.empty
    max = 1.0 / 0.0
    min = -max

    Interval.new(max, min)
  end

  def self.encompassing(xs)
    Interval.new(xs.min, xs.max)
  end
  
  attr_reader :min, :max

  def merge(other)
    Interval.new( [ min, other.min ], [ max, other.max ] )
  end
end


class Box
  def initialize(x, y, z)
    raise "Type error: #{x} should be an interval" unless Interval === x
    raise "Type error: #{y} should be an interval" unless Interval === y
    raise "Type error: #{z} should be an interval" unless Interval === z
    
    @x, @y, @z = x, y, z
  end

  def self.empty
    Box.new(Interval.empty, Interval.empty, Interval.empty)
  end

  attr_reader :x, :y, :z

  def merge(other)
    Box.new( x.merge(other.x), y.merge(other.y), z.merge(other.z) )
  end
end


def load_raw(file)
  raise "Expected 'raw' on first line" unless file.readline.strip == 'raw'
  n_vertices = file.readline.to_i

  vertices = []
  n_vertices.times do
    vertices << Vertex.new(*file.readline.strip.split(/ /).map(&:to_f))
  end

  n_triangles = file.readline.to_i

  triangles = []
  n_triangles.times do
    triangles << Triangle.new(*file.readline.strip.split(/ /).map(&:to_i))
  end

  { :vertices => vertices, :triangles => triangles }
end


def write_vertices(vertices)
  puts vertices.size
  
  vertices.each do |vertex|
    puts "#{vertex.x} #{vertex.y} #{vertex.z}"
  end
end


def write_triangles(triangles)
  puts triangles.size

  triangles.each do |triangle|
    puts "#{triangle.a} #{triangle.b} #{triangle.c}"
  end
end


def write(vertices, triangles)
  puts "raw"
  write_vertices(vertices)
  write_triangles(triangles)
end
