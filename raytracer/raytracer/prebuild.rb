/BUILD_NUMBER (\d+)/ =~ IO.read('version.h')
build_number = $1.to_i
next_build_number = build_number + 1

File.open('version.h', 'w') do |out|
  out.puts "#define BUILD_NUMBER #{next_build_number}"
end
