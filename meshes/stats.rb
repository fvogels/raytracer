require './shared.rb'

data = load_raw(STDIN)

vertices = data[:vertices]
triangles = data[:triangles]

puts "#{vertices.size} vertices"
puts "#{triangles.size} triangles"

min_x = vertices.map(&:x).min
min_y = vertices.map(&:y).min
min_z = vertices.map(&:z).min
max_x = vertices.map(&:x).max
max_y = vertices.map(&:y).max
max_z = vertices.map(&:z).max

puts "X: [#{min_x}, #{max_x}]"
puts "Y: [#{min_y}, #{max_y}]"
puts "Z: [#{min_z}, #{max_z}]"

puts "DX = #{max_x - min_x}"
puts "DY = #{max_y - min_y}"
puts "DZ = #{max_z - min_z}"
