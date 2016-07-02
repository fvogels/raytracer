Vertex = Struct.new(:x, :y, :z)
Triangle = Struct.new(:i, :j, :k)

def read_header(file)
  data = {}

  abort "Expected 'ply' as first line" unless file.readline.strip == 'ply'
  
  while (line = file.readline.strip) != 'end_header'
    case line
    when /^element/
    then
      parts = line.split(/ /)
      current_element = parts[1]
      data[current_element] = { :count => parts[2].to_i, :properties => [] }

    when /^property/
    then
      parts = line.split(/ /)
      data[current_element][:properties] << parts[1..-1]

    when /^comment/
    then nil

    else
      STDERR.puts "Ignoring header line #{line}"
    end
  end

  data
end

def read_vertices(file, header_data)
  vertices = []

  x_index = header_data['vertex'][:properties].find_index { |parts| parts[1] == 'x' }
  y_index = header_data['vertex'][:properties].find_index { |parts| parts[1] == 'y' }
  z_index = header_data['vertex'][:properties].find_index { |parts| parts[1] == 'z' }

  abort "Missing x y z properties" unless (x_index and y_index and z_index)

  header_data['vertex'][:count].times do
    line = file.readline.strip
    parts = line.split(/ /)

    x = parts[x_index].to_f
    y = parts[y_index].to_f
    z = parts[z_index].to_f

    vertices << Vertex.new(x, y, z)
  end

  vertices
end

def read_faces(file, header_data, vertices)
  faces = []

  header_data['face'][:count].times do
    line = file.readline.strip
    parts = line.split(/ /)

    abort "All faces must be triangles" unless parts[0].to_i == 3

    vertex_indices = parts[1..-1].map(&:to_i)

    faces << Triangle.new(*vertex_indices)
  end

  faces
end

def main
  header_data = read_header(STDIN)
  vertices = read_vertices(STDIN, header_data)
  faces = read_faces(STDIN, header_data, vertices)
  
  puts vertices.size
  vertices.each do |vertex|
    puts "#{vertex.x} #{vertex.y} #{vertex.z}"
  end
  puts faces.size
  faces.each do |face|
    puts "#{face.i} #{face.j} #{face.k}"
  end
end


main
