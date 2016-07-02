Vertex = Struct.new(:x, :y, :z)
Triangle = Struct.new(:a, :b, :c)

n_vertices = STDIN.readline.to_i
puts "#{n_vertices} vertices"

vertices = []
n_vertices.times do
  vertices << Vertex.new(*STDIN.readline.strip.split(/ /).map(&:to_f))
end

n_triangles = STDIN.readline.to_i
puts "#{n_triangles} triangles"

triangles = []
n_triangles.times do
  triangles << Triangle.new(*STDIN.readline.strip.split(/ /).map(&:to_i))
end

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

