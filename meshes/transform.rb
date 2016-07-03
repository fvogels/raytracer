require './shared.rb'
require 'optparse'


data = load(STDIN)

$vertices = data[:vertices]
$triangles = data[:triangles]

def x_coords
  $vertices.map(&:x)
end

def y_coords
  $vertices.map(&:y)
end

def z_coords
  $vertices.map(&:z)
end

def scale(factor)
  $vertices.map! do |vertex|
    Vertex.new(vertex.x * factor, vertex.y * factor, vertex.z * factor)
  end
end

def translate(dx, dy, dz)
  $vertices.map! do |vertex|
    Vertex.new(vertex.x + dx, vertex.y + dy, vertex.z + dz)
  end
end

OptionParser.new do |opts|
  opts.on("--scale ARG", "Scale uniformly") do |arg|
    case arg.downcase
    when 'x'
    then
      coords = x_coords
      factor = 1 / (coords.max - coords.min)
    when 'y'
    then
      coords = y_coords
      factor = 1 / (coords.max - coords.min)
    when 'z'
    then
      coords = z_coords
      factor = 1 / (coords.max - coords.min)
    when /^[0-9.]+$/
    then
      factor = arg.to_f
    end

    scale(factor)
  end

  opts.on("--center", "Center mesh around origin") do |arg|
    xs = x_coords
    ys = y_coords
    zs = z_coords

    dx = (xs.max + xs.min) / 2
    dy = (ys.max + ys.min) / 2
    dz = (zs.max + zs.min) / 2

    translate(-dx, -dy, -dz)
  end
end.parse!


write($vertices, $triangles)


