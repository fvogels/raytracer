def convert_to_binary(input_pathname, output_pathname)
  input_pathname.open('r') do |input|
    output_pathname.open('wb') do |file|
      n_vertices, n_normals = input.gets.strip.split.map(&:to_i)
      file.write([ n_vertices, n_normals ].pack('II'))

      n_vertices.times do
        vertex = input.gets.split.map(&:to_f)
        file.write(vertex.pack('DDD'))
      end

      n_normals.times do
        normal = input.gets.split.map(&:to_f)
        file.write(normal.pack('DDD'))
      end

      while (line = input.gets.strip) != 'end'
        tag, *args = line.split

        case tag
        when 'b'
          n_children = args[0].to_i
          file.write([0, n_children].pack('II'))

        when 't'
          vertex_indices = args.map(&:to_i)
          file.write([1, *vertex_indices].pack('IIII'))
        end
      end

      file.write([0xFFFFFFFF].pack('I'))
    end
  end
end