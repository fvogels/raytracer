Vertex = Struct.new(:x, :y, :z)
Triangle = Struct.new(:a, :b, :c)

def load(file)
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


def write(vertices, triangles)
  puts vertices.size
  
  vertices.each do |vertex|
    puts "#{vertex.x} #{vertex.y} #{vertex.z}"
  end

  puts triangles.size

  triangles.each do |triangle|
    puts "#{triangle.a} #{triangle.b} #{triangle.c}"
  end
end
