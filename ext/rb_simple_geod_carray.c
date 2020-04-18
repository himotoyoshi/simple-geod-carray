#include "ruby.h"
#include "carray.h"
#include "rb_geod.h"

/*
 *  call-seq:
 *     Geod#direct_ca(lat1, lon1, az12, dist, lat2, lon2, az21)  ->  nil
 *     Geod#forward_ca(lat1, lon1, az12, dist, lat2, lon2, az21)  ->  nil
 * 
 *  Calculates the latitude, longitude and back azimuth of a terminus point
 *  given a initial point latitude, longitude, azimuth and  distance.
 *  The latitude should be a floating point value in degrees, which
 *  positive value means northern direction. The longitude should be a
 *  floating point value in degrees, which positive value means western
 *  direction. The returned array contains the latitude, longitude and
 *  back azimuth at the terminus point in degrees.
 *
 *    input:
 *
 *      lat1, lon1, az12, dist
 *         read only CArray.double or its convertible
 *
 *    output:
 *
 *      lat2, lon2, az21
 *         writable CArray.double or its convertible
 *
 */

static VALUE
rb_geodesic_direct_ca (VALUE self, 
                       volatile VALUE vlat1, volatile VALUE vlon1, 
                       volatile VALUE vaz12, volatile VALUE vdist, 
                       volatile VALUE vlat2, volatile VALUE vlon2, 
                       volatile VALUE vaz21)
{
  Geodesic *geodesic;
  CArray *lat1, *lon1, *az12, *dist, *lat2, *lon2, *az21;
  double *p1, *p2, *p3, *p4, *p5, *p6, *p7;
  ca_size_t  s1,  s2,  s3,  s4,  s5,  s6,  s7;
  int8_t  *m, *mp;
  ca_size_t  count;
  ca_size_t i;

  Data_Get_Struct(self, Geodesic, geodesic);

  lat1 = ca_wrap_readonly(vlat1, CA_DOUBLE);
  lon1 = ca_wrap_readonly(vlon1, CA_DOUBLE); 
  az12 = ca_wrap_readonly(vaz12, CA_DOUBLE);
  dist = ca_wrap_readonly(vdist, CA_DOUBLE);
  lat2 = ca_wrap_writable(vlat2, CA_DOUBLE);
  lon2 = ca_wrap_writable(vlon2, CA_DOUBLE);
  az21 = ca_wrap_writable(vaz21, CA_DOUBLE);

  ca_attach_n(7, lat1, lon1, dist, az12, lat2, lon2, az21);

  count = ca_set_iterator(7, 
                          lat1, &p1, &s1,
                          lon1, &p2, &s2,
                          az12, &p3, &s3,
                          dist, &p4, &s4,
                          lat2, &p5, &s5,
                          lon2, &p6, &s6,
                          az21, &p7, &s7);

  m = ca_allocate_mask_iterator(4, lat1, lon1, az12, dist);

  mp = m;
  for (i=0; i<count; i++) {
    if ( *mp ) {
      *p5 = 0.0/0.0;
      *p6 = 0.0/0.0;
      *p7 = 0.0/0.0;
    }
    else {
      geod_direct(geodesic->ref, *p1, *p2, *p3, *p4, p5, p6, p7);
    }
    p1+=s1; p2+=s2; p3+=s3; p4+=s4; p5+=s5; p6+=s6; p7+=s7;
    mp++;
  }

  free(m);

  ca_sync_n(3, lat2, lon2, az21);
  ca_detach_n(7, lat1, lon1, dist, az12, lat2, lon2, az21);
  
  return Qnil;
}

/*
 *  call-seq:
 *     Geod.invgeod_d(lat1,lon1,lat2,lon2,dist,az12,az21)  ->  nil
 * 
 *  Calculates the forward and back azimuths and distance
 *  between an initial and terminus point latitudes and longitudes.
 *  The latitude should be a floating point value in degrees, which
 *  positive value means northern direction. The longitude should be a
 *  floating point value in degrees, which positive value means western
 *  direction. The returned array contains the forward and back azimuths 
 *  in degrees and distance in the metric specified by +Geod.init+.
 *
 *    input:
 *
 *      lat1, lon1, lat2, lon2
 *         read only CArray.double or its convertible
 *
 *    output:
 *
 *      dist, az12, az21 
 *         writable CArray.double or its convertible
 *
 */

static VALUE
rb_geodesic_inverse_ca (VALUE self, 
                    volatile VALUE vlat1, volatile VALUE vlon1, 
                    volatile VALUE vlat2, volatile VALUE vlon2,
                    volatile VALUE vdist, volatile VALUE vaz12, 
                    volatile VALUE vaz21)
{
  Geodesic *geodesic;
  CArray *lat1, *lon1, *lat2, *lon2, *dist, *az12, *az21;
  double *p1, *p2, *p3, *p4, *p5, *p6, *p7;
  ca_size_t     s1,  s2,  s3,  s4,  s5,  s6,  s7;
  int8_t  *m, *mp;
  ca_size_t    count;
  ca_size_t i;

  Data_Get_Struct(self, Geodesic, geodesic);

  lat1 = ca_wrap_readonly(vlat1, CA_DOUBLE);
  lon1 = ca_wrap_readonly(vlon1, CA_DOUBLE); 
  lat2 = ca_wrap_readonly(vlat2, CA_DOUBLE);
  lon2 = ca_wrap_readonly(vlon2, CA_DOUBLE);
  dist = ca_wrap_writable(vdist, CA_DOUBLE);
  az12 = ca_wrap_writable(vaz12, CA_DOUBLE);
  az21 = ca_wrap_writable(vaz21, CA_DOUBLE);

  ca_attach_n(7, lat1, lon1, lat2, lon2, dist, az12, az21);

  count = ca_set_iterator(7, 
                          lat1, &p1, &s1,
                          lon1, &p2, &s2,
                          lat2, &p3, &s3,
                          lon2, &p4, &s4,
                          dist, &p5, &s5,
                          az12, &p6, &s6,
                          az21, &p7, &s7);

  m = ca_allocate_mask_iterator(4, lat1, lon1, lat2, lon2);

  mp = m;
  for (i=0; i<count; i++) {
    if ( *mp ) {
      *p5 = 0.0/0.0;
      *p6 = 0.0/0.0;
      *p7 = 0.0/0.0;
    }
    else {
      geod_inverse(geodesic->ref, *p1, *p2, *p3, *p4, p5, p6, p7);
    }
    p1+=s1; p2+=s2; p3+=s3; p4+=s4; p5+=s5; p6+=s6; p7+=s7;
    mp++;
  }

  free(m);

  ca_sync_n(3, dist, az12, az21);
  ca_detach_n(7, lat1, lon1, lat2, lon2, dist, az12, az21);
  
  return Qnil;
}

static VALUE
rb_geodesic_distance_ca (VALUE self, 
                         volatile VALUE vlat1, volatile VALUE vlon1, 
                         volatile VALUE vlat2, volatile VALUE vlon2,
                         volatile VALUE vdist)
{
  Geodesic *geodesic;
  CArray *lat1, *lon1, *lat2, *lon2, *dist;
  double *p1, *p2, *p3, *p4, *p5;
  double  d0; 
  ca_size_t  s1,  s2,  s3,  s4,  s5;
  int8_t  *m, *mp;
  ca_size_t    count;
  ca_size_t i;

  Data_Get_Struct(self, Geodesic, geodesic);

  lat1 = ca_wrap_readonly(vlat1, CA_DOUBLE);
  lon1 = ca_wrap_readonly(vlon1, CA_DOUBLE); 
  lat2 = ca_wrap_readonly(vlat2, CA_DOUBLE);
  lon2 = ca_wrap_readonly(vlon2, CA_DOUBLE);
  dist = ca_wrap_writable(vdist, CA_DOUBLE);

  ca_attach_n(5, lat1, lon1, lat2, lon2, dist);

  count = ca_set_iterator(5, 
                          lat1, &p1, &s1,
                          lon1, &p2, &s2,
                          lat2, &p3, &s3,
                          lon2, &p4, &s4,
                          dist, &p5, &s5);

  m = ca_allocate_mask_iterator(4, lat1, lon1, lat2, lon2);

  mp = m;
  for (i=0; i<count; i++) {
    if ( *mp ) {
      *p5 = 0.0/0.0;
    }
    else {
      geod_inverse(geodesic->ref, *p1, *p2, *p3, *p4, &d0, 0, 0);
      *p5 = d0;
    }
    p1+=s1; p2+=s2; p3+=s3; p4+=s4; p5+=s5;
    mp++;
  }

  free(m);

  ca_sync(dist);
  ca_detach_n(5, lat1, lon1, lat2, lon2, dist);
  
  return Qnil;
}

void
Init_simple_geod_carray ()
{
  extern VALUE rb_cGeodesic;
  rb_define_private_method(rb_cGeodesic, "_direct_ca",   rb_geodesic_direct_ca,   7);
  rb_define_private_method(rb_cGeodesic, "_forward_ca",  rb_geodesic_direct_ca,   7);
  rb_define_private_method(rb_cGeodesic, "_inverse_ca",  rb_geodesic_inverse_ca,  7);
  rb_define_private_method(rb_cGeodesic, "_distance_ca", rb_geodesic_distance_ca, 5);
}

