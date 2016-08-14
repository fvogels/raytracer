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
  def template(&block)
    @template = block
    @tests = []
  end

  def test_case
    data = Store.new
    yield data
    test_code = data.instance_eval(&@template)

    @tests << test_code.unindent
  end

  attr_reader :tests
end


class TestFileContext
  def template
    @template = yield.unindent
  end
  
  def test_suite(&block)
    context = TestSuiteContext.new
    context.instance_eval(&block)
    tests = context.tests

    @template.gsub(%r{<<<TESTS>>>}, tests.join("\n\n"))
  end
end


def test_file(filename, &block)
  context = TestFileContext.new
  source = context.instance_eval(&block)

  File.open("../tests/#{filename}.cpp", 'w') do |out|
    out.puts source
  end
end
