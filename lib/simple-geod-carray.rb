require "simple-geod"
require "carray"
require "simple_geod_carray.so"

class GEOD

  #
  #
  #
  def direct_carray (lat1, lon1, az12, dist)
    argv = [lat1, lon1, az12, dist].map{|a| a.is_a?(CArray) ? a : CA_DOUBLE(a) }
    lat1, lon1, az12, dist = *argv
    ref  = argv[argv.map(&:size).to_ca.max_addr]
    lon2 = ref.template
    lat2 = ref.template
    az21 = ref.template
    _forward_ca(lat1, lon1, az12, dist, lat2, lon2, az21)
    return lat2, lon2, az21
  end

  alias direct_latlon_carray direct_carray
  
  def direct_lonlat_carray (lon1, lat1, az12, s12)
    return direct_carray(lat1, lon1, az12, s12)
  end
  
  #
  #
  #
  def inverse_carray (lat1, lon1, lat2, lon2)
    argv = [lat1, lon1, lat2, lon2].map{|a| a.is_a?(CArray) ? a : CA_DOUBLE(a) }
    lat1, lon1, lat2, lon2 = *argv
    ref  = argv[argv.map(&:size).to_ca.max_addr]
    dist = ref.template
    az12 = ref.template
    az21 = ref.template
    _inverse_ca(lat1, lon1, lat2, lon2, dist, az12, az21)
    return dist, az12, az21
  end

  alias inverse_latlon_carray inverse_carray
  
  def inverse_lonlat_carray (lon1, lat1, lon2, lat2)
    return inverse_carray(lat1, lon1, lat2, lon2)
  end

  #
  #
  #
  def distance_carray (lat1, lon1, lat2, lon2)
    argv = [lat1, lon1, lat2, lon2].map{|a| a.is_a?(CArray) ? a : CA_DOUBLE(a) }
    lat1, lon1, lat2, lon2 = *argv
    ref = argv[argv.map(&:size).to_ca.max_addr]
    dist = ref.template
    _distance_ca(lat1, lon1, lat2, lon2, dist)
    return dist
  end

  alias distance_latlon_carray distance_carray
  
  def distance_lonlat_carray (lon1, lat1, lon2, lat2)
    return distance_carray(lat1, lon1, lat2, lon2)
  end
  
end

