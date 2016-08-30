require 'fileutils'
require 'pathname'


class Store
  def initialize
    @members = {}
  end
  
  def method_missing(method_name, *args, &block)
    if /^(.*)=/ =~ method_name.to_s
    then
      field_name = $1

      if @members.has_key? field_name
      then raise "Error: writing same field #{field_name} twice"
      else @members[field_name] = args[0]
      end
    else
      field_name = method_name.to_s

      if @members.has_key? field_name
      then @members[field_name]
      else raise "Error: reading nonexistent field #{field_name}\nFields: #{@members.keys.join(' ')}"
      end
    end
  end
end


class String
  def unindent
    indentation = lines.select do |line|
      line.strip.length > 0
    end.map do |line|
      /^( *)/ =~ line
      $1.length
    end.min

    lines.map do |line|
      if line.strip.length > 0
      then line.rstrip[indentation..-1]
      else ""
      end
    end.join("\n")
  end
end


class TestSuiteContext
  def initialize
    @tests = []
  end

  def template(&block)
    @template = block
  end

  def test_case
    if not @template then
      raise "Missing template"
    else    
      data = Store.new
      yield data
      test_code = data.instance_eval(&@template)

      @tests << test_code.unindent
    end
  end

  attr_reader :tests
end


class TestFileContext
  def initialize
    @tests = []
  end
  
  def template
    @template = yield.unindent
  end
  
  def test_suite(&block)
    context = TestSuiteContext.new
    context.instance_eval(&block)
    tests = context.tests

    @tests += tests
  end

  def generate_source
    if not @template then
      raise "Missing template"
    else
      @template.gsub(%r{<<<TESTS>>>}, @tests.join("\n\n"))
    end
  end

  attr_reader :tests
end


def test_file(test_path, &block)
  puts
  puts "Generating tests #{test_path}"
  
  context = TestFileContext.new
  context.instance_eval(&block)
  tests_source = context.generate_source

  path = Pathname.new("../tests/#{test_path}-tests.cpp").expand_path


  if path.file? then
    puts "#{path} already exists; comparing contents..."
    old_tests_source = path.read

    if old_tests_source == tests_source
    then
      puts "Contents are the same"
      puts "SKIPPED #{path}"
      return
    else
      puts "Contents are different"
    end
  end

  FileUtils.mkdir_p path.parent.expand_path.to_s
  puts "Writing #{path}"
  path.write tests_source
  puts "WROTE #{path}"
end
