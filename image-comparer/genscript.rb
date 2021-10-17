versions = <<END.split.map(&:strip)
random(1)
random(2)
random(3)
nrooks(1)
nrooks(2)
nrooks(3)
stratified(1,1)
stratified(2,2)
stratified(3,3)
jittered(1,1)
jittered(2,2)
jittered(3,3)
halfjittered(1,1)
halfjittered(2,2)
halfjittered(3,3)
multijittered(1)
multijittered(2)
multijittered(3)
multijittered(5)
END


versions.each do |version|
  filename = version.gsub('(','').gsub(')','').gsub(',','-')
  puts "cat test.chai | sed 's/SAMPLER/#{version}/' | /g/repos/ucll/3dcg/raytracer/raytracer/x64/Release/raytracer.exe -s - > #{filename}.wif"
end
