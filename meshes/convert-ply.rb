Vertex = Struct.new(:x, :y, :z)
Triangle = Struct.new(:i, :j, :k)

def read_header(file)
  data = {}

  abort "Expected 'ply' as first line" unless file.readline.strip == 'ply'

  data[:format] = case line = file.readline.strip
                  when 'format binary_big_endian 1.0'
                  then :big_endian
                  when 'format ascii 1.0'
                  then :ascii
                  else
                    raise "Unknown format: #{line}"
                  end
  
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
  case header_data[:format]
  when :ascii
  then
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
    
  when :big_endian
  then
    if header_data['vertex'][:properties].size != 3
    then abort "Expected 3 vertex properties"
    end

    (1..header_data['vertex'][:count]).map do
      coords = file.read(12).unpack('ggg')
      Vertex.new(*coords)
    end

  else
    abort "Unknown format"
  end
end

def read_faces(file, header_data, vertices)
  case header_data[:format]
  when :ascii
    faces = []

    header_data['face'][:count].times do
      line = file.readline.strip
      parts = line.split(/ /)

      abort "All faces must be triangles" unless parts[0].to_i == 3

      vertex_indices = parts[1..-1].map(&:to_i)

      faces << Triangle.new(*vertex_indices)
    end

    faces

  when :big_endian
    (1..header_data['face'][:count]).map do
      n = file.read(1).unpack('C')[0]

      abort "All faces must be triangles -- found face with #{n} sides" unless n == 3

      indices = file.read(12).unpack('NNN')

      indices.each do |index|
        if index >= vertices.size
        then abort "Index out of bounds: #{index} >= #{vertices.size}"
        end
      end
      
      Triangle.new(*indices)
    end

  else
    abort "Unknown format"
  end
end

def main
  header_data = read_header(STDIN)
  vertices = read_vertices(STDIN, header_data)
  faces = read_faces(STDIN, header_data, vertices)

  puts "raw"
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
