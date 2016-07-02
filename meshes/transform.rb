require './shared.rb'
require 'optparse'


data = load(STDIN)

$vertices = data[:vertices]
$triangles = data[:triangles]


def resize(factor)
  $vertices = $vertices.map do |vertex|
    Vertex.new(vertex.x / factor, vertex.y / factor, vertex.z / factor)
  end
end


OptionParser.new do |opts|
  opts.on("--resize AXIS", "Scale uniformly so that mesh has size 1 in given dimension") do |axis|
    case axis.downcase
    when 'x'
    then
      coords = $vertices.map(&:x)
    when 'y'
    then
      coords = $vertices.map(&:y)
    when 'z'
    then
      coords = $vertices.map(&:z)
    end

    resize(coords.max - coords.min)
  end
end.parse!


write($vertices, $triangles)


