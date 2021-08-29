module Obj2Mesh

  class TriangleVertex
    def initialize(v, vt=nil, vn=nil)
      @v = v
      @vt = vt.empty? ? nil : vt
      @vn = vn
    end

    attr_reader :v, :vt, :vn
  end

  class Converter
    def initialize(input, output)
      @vertices = []
      @normals = []
      @triangles = []
      @input = input
      @output = output
    end

    def process
      read_data
      write_data
    end

    def read_data
      @input.each_line.with_index do |line, line_index|
        process_line(line, line_index)
      end
    end

    def write_data
      @normals = [] # TODO Get rid of this

      @output.puts "#{@vertices.size} #{@normals.size}"

      @vertices.each do |vertex|
        @output.puts(vertex.join(' '))
      end

      @normals.each do |normal|
        @output.puts(normal.join(' '))
      end

      @triangles.each do |vertices|
        # raise 'Unsupported vt/vn' if vertices[0].vt or vertices[0].vn

        vertices_string = vertices.map { |v| v.v.to_i - 1 }.join(' ')
        @output.puts("t #{vertices_string}")
      end

      @output.puts "end"
    end

    def process_line(line, line_index)
      line = remove_comments line

      unless line.empty?
        case find_tag line
        when 'v'
          process_vertex_line(line, line_index)

        when 'vn'
          process_normal_line(line, line_index)

        when 'vt'
          process_texture_line(line, line_index)

        when 'g'
          process_group_line(line, line_index)

        when 'o'
          process_object_line(line, line_index)

        when 'mtllib'
          process_material_library_line(line, line_index)

        when 'usemtl'
          process_material_line(line, line_index)

        when 's'
          process_smooth_shading_line(line, line_index)

        when 'f'
          process_face_line(line, line_index)

        else
          raise "Unrecognized tag #{tag} on line #{line_index + 1}"
        end
      end
    end

    def find_tag(line)
      line.split(' ').first
    end

    def process_smooth_shading_line(line, line_index)
      # NOP
    end

    def process_object_line(line, line_index)
      # NOP
    end

    def process_group_line(line, line_index)
      # NOP
    end

    def process_material_library_line(line, line_index)
      # NOP
    end

    def process_material_line(line, line_index)
      # NOP
    end

    def process_texture_line(line, line_index)
      # NOP
    end

    def process_face_line(line, line_index)
      vertices = line.split(' ')[1..-1]

      case vertices.size
      when 3
        process_triangle(vertices)

      when 4
        process_triangle([vertices[0], vertices[1], vertices[2]])
        process_triangle([vertices[2], vertices[3], vertices[0]])

      else
        raise "Face with #{vertices.size} on line #{line_index + 1}"
      end
    end

    def process_triangle(vertices)
      vertices.map! do |vertex|
        parts = vertex.split('/')
        TriangleVertex.new(*parts)
      end

      @triangles << vertices
    end

    def process_vertex_line(line, line_index)
      coords = line.split(' ')[1..-1]
      @vertices << coords
    end

    def process_normal_line(line, line_index)
      coords = line.split(' ')[1..-1]
      @normals << coords
    end

    def remove_comments(line)
      line.gsub(/#.*/, '').strip
    end
  end
end


def convert_obj_to_mesh(input_pathname, output_pathname)
  input_pathname.open do |input|
    output_pathname.open('w') do |output|
      Obj2Mesh::Converter.new(input, output).process
    end
  end
end