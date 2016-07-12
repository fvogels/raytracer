require 'open3'


def generate_script(plot_string)
  <<-END.lines.map { |x| x.strip }.join("\n")
set terminal png;
unset autoscale;
set xrange [0:1];
set yrange [0:1];
unset key;
set linetype 1 lw 4;
plot #{plot_string};
  END
end

def generate_animation(frame_count, output_file)
  data = (1..frame_count).map do |i|
    script = generate_script(yield i)
    png_image, result = Open3.capture2(%{gnuplot -e "#{script}"}, :binmode => true)
    ppm_image, result = Open3.capture2(%{convert png:- ppm:-}, :stdin_data => png_image, :binmode => true)
    ppm_image
  end.join('')

  Open3.capture2("convert ppm:- -delay 25 -loop 0 #{output_file}", :stdin_data => data)
end


generate_animation(30, 'linear.gif') do |i|
  max_x = i / 30.0
  
  "x < #{max_x} ? x : 1/0"
end

generate_animation(30, 'quadratic-o.gif') do |i|
  max_x = i / 30.0
  
  "x < #{max_x} ? x**2 : 1/0"
end
