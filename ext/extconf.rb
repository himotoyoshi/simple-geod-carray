require "mkmf"
require "carray/mkmf"

if defined?(Gem)
  if Gem::VERSION >= "1.7.0"    
    rb_geod_include = [$sitearchdir, *Gem::Specification.find_all_by_name("simple-geod").map { |s| File.join(s.gem_dir,"ext") }]
  else
    rb_geod_include = [$sitearchdir, *Gem.all_load_paths.reverse.grep(/simple-geod/)]
  end
else
  rb_geod_include = [$sitearchdir]
end

dir_config("geod", rb_geod_include, "")

if have_header("geodesic.h") and have_header("rb_geod.h") 
  have_carray()
  create_makefile("simple_geod_carray")
end
