require './shared.rb'

def convert_bbh(input, output)
  output.write([12345].pack('V'))
  
  n_vertices = input.readline.strip.to_i
  output.write([ n_vertices ].pack('V'))

  n_vertices.times do
    coordinates = input.readline.strip.split(/ /).map(&:to_f)
    abort "Wrong number of coordinates" unless coordinates.size == 3
    output.write(coordinates.pack('eee'))
  end

  while (line = input.readline.strip) != 'end'
    parts = line.split(/ /)
    
    case parts[0]
    when 't'
    then output.write(([0x11111111] + parts[1..3].map(&:to_i)).pack('VVVV'))
    when 'g'
    then output.write([0x22222222].pack('V'))
    end
  end

  output.write([0xFFFFFFFF].pack('V'))
end

def convert(input, output)
  case tag = input.readline.strip
  when 'bbh'
  then convert_bbh(input, output)
  else
    raise "Tag #{tag} not supported"
  end
end

if ARGV.size == 1 then
  open(ARGV[0], 'wb') do |out|
    convert(STDIN, out)
  end
else
  STDERR.puts "Does not work with piping! Specify output file!"
end
