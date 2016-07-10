require './shared.rb'
require 'optparse'

class Cell
  def initialize(&block)
    @dirty = true
    @observers = []
    @recomputer = block
  end
  
  def value
    clean
    @value
  end

  def value=(x)
    @value = x
    @observers.each { |observer| observer[] }
  end

  def make_dirty
    @dirty = true
  end

  def clean
    if @dirty
    then
      recompute
      @dirty = false
    end
  end

  def observe(&block)
    @observers << block
  end

  def recompute
    @value = @recomputer[]
  end
end

def derived_cell(original, &block)
  result = Cell.new do
    block[original.value]
  end
  
  original.observe do
    result.make_dirty
  end

  result
end


data = load_raw(STDIN)

$vertices = Cell.new { data[:vertices] }
$triangles = Cell.new { data[:triangles] }

$x_coords = derived_cell($vertices) { |vertices| vertices.map(&:x) }
$y_coords = derived_cell($vertices) { |vertices| vertices.map(&:y) }
$z_coords = derived_cell($vertices) { |vertices| vertices.map(&:z) }

def x_coords
  $x_coords.value
end

def y_coords
  $y_coords.value
end

def z_coords
  $z_coords.value
end

def scale(factor)
  $vertices.value = $vertices.value.map do |vertex|
    Vertex.new(vertex.x * factor, vertex.y * factor, vertex.z * factor)
  end
end

def translate(dx, dy, dz)
  $vertices.value = $vertices.value.map do |vertex|
    Vertex.new(vertex.x + dx, vertex.y + dy, vertex.z + dz)
  end
end

OptionParser.new do |opts|
  opts.on("--scale ARG", "Scale uniformly") do |arg|
    case arg.downcase
    when 'x'
    then
      factor = 1 / (x_coords.max - x_coords.min)
    when 'y'
    then
      factor = 1 / (y_coords.max - y_coords.min)
    when 'z'
    then
      factor = 1 / (z_coords.max - z_coords.min)
    when /^[0-9.]+$/
    then
      factor = arg.to_f
    end

    scale(factor)
  end

  opts.on("--center", "Center mesh around origin") do |arg|
    dx = (x_coords.max + x_coords.min) / 2
    dy = (y_coords.max + y_coords.min) / 2
    dz = (z_coords.max + z_coords.min) / 2

    translate(-dx, -dy, -dz)
  end

  opts.on("--corner", "Center mesh around origin") do |arg|
    dx = x_coords.min
    dy = y_coords.min
    dz = z_coords.min

    translate(-dx, -dy, -dz)
  end
end.parse!


write($vertices.value, $triangles.value)

