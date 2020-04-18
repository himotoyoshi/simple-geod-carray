
Gem::Specification::new do |s|
  version = "1.0.0"

  files = Dir.glob("**/*") - [ 
                               Dir.glob("simple-geod-carray-*.gem"), 
                             ].flatten

  s.platform    = Gem::Platform::RUBY
  s.name        = "simple-geod-carray"
  s.summary     = "An extension library for geod gem to use carray"
  s.description = <<-HERE
    An extension library for geod gem to use carray
  HERE
  s.version     = version
  s.licenses    = ['MIT']
  s.author      = "Hiroki Motoyoshi"
  s.email       = ""
  s.homepage    = 'https://github.com/himotoyoshi/geod'
  s.files       = files
  s.extensions  = [ "ext/extconf.rb" ]
  s.required_ruby_version = ">= 1.8.1"
  s.add_runtime_dependency 'simple-geod',  '~> 1.0', '>= 1.0.0'
  s.add_runtime_dependency 'carray', '~> 1.3', '>= 1.3.0'
end
