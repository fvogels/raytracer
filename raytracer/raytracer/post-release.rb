require 'fileutils'

exe_path = ARGV[0]
output_path = "E:/repos/ucll/shared/scripts/"
puts "Post Release Build Script"
puts "Copying #{exe_path} to #{output_path}"
FileUtils.cp(exe_path, output_path)
