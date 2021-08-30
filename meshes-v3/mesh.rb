#!/usr/bin/env ruby
require 'commander/import'
require 'pathname'
require_relative 'scripts/obj2mesh'
require_relative 'scripts/binary'
require_relative 'scripts/optimization'



program :name, 'Mesh'
program :version, '3.0.0'
program :description, 'Processes meshes'


command :optimize do |c|
  c.syntax = 'optimize IN OUT'
  c.description = 'optimizes mesh'

  c.action do |args, options|
    abort 'Two arguments required' unless args.size == 2

    in_path = Pathname.new args[0]
    out_path = Pathname.new args[1]

    optimize(in_path, out_path)
  end
end

command :binary do |c|
  c.syntax = 'binary IN OUT'
  c.description = 'makes binary version'

  c.action do |args, options|
    abort 'Two arguments required' unless args.size == 2

    in_path = Pathname.new args[0]
    out_path = Pathname.new args[1]

    convert_to_binary(in_path, out_path)
  end
end

command :obj2mesh do |c|
  c.syntax = 'obj2mesh IN OUT'
  c.description = 'converts .obj to .mesh'

  c.action do |args, options|
    abort 'Two arguments required' unless args.size == 2

    in_path = Pathname.new args[0]
    out_path = Pathname.new args[1]

    convert_obj_to_mesh(in_path, out_path)
  end
end

