Dir['*.rb'].select do |file|
  # Select all ruby files except this one
  /generate-all-tests/ !~ file
end.each do |file|
  require "./#{file}"
end
