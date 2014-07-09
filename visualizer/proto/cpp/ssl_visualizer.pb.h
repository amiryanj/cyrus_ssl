// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ssl_visualizer.proto

#ifndef PROTOBUF_ssl_5fvisualizer_2eproto__INCLUDED
#define PROTOBUF_ssl_5fvisualizer_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

//#if GOOGLE_PROTOBUF_VERSION < 2004000
//#error This file was generated by a newer version of protoc which is
//#error incompatible with your Protocol Buffer headers.  Please update
//#error your headers.
//#endif
//#if 2004001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
//#error This file was generated by an older version of protoc which is
//#error incompatible with your Protocol Buffer headers.  Please
//#error regenerate this file with a newer version of protoc.
//#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_message_reflection.h>
#include "ssl_world.pb.h"
#include "ssl_analyzer.pb.h"
#include "ssl_decision.pb.h"
#include "ssl_planner.pb.h"
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_ssl_5fvisualizer_2eproto();
void protobuf_AssignDesc_ssl_5fvisualizer_2eproto();
void protobuf_ShutdownFile_ssl_5fvisualizer_2eproto();

class ssl_visualizer_packet;

// ===================================================================

class ssl_visualizer_packet : public ::google::protobuf::Message {
 public:
  ssl_visualizer_packet();
  virtual ~ssl_visualizer_packet();
  
  ssl_visualizer_packet(const ssl_visualizer_packet& from);
  
  inline ssl_visualizer_packet& operator=(const ssl_visualizer_packet& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const ssl_visualizer_packet& default_instance();
  
  void Swap(ssl_visualizer_packet* other);
  
  // implements Message ----------------------------------------------
  
  ssl_visualizer_packet* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ssl_visualizer_packet& from);
  void MergeFrom(const ssl_visualizer_packet& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // optional .ssl_world_packet world_data = 1;
  inline bool has_world_data() const;
  inline void clear_world_data();
  static const int kWorldDataFieldNumber = 1;
  inline const ::ssl_world_packet& world_data() const;
  inline ::ssl_world_packet* mutable_world_data();
  inline ::ssl_world_packet* release_world_data();
  
  // optional .ssl_analyzer_packet analyzer_data = 2;
  inline bool has_analyzer_data() const;
  inline void clear_analyzer_data();
  static const int kAnalyzerDataFieldNumber = 2;
  inline const ::ssl_analyzer_packet& analyzer_data() const;
  inline ::ssl_analyzer_packet* mutable_analyzer_data();
  inline ::ssl_analyzer_packet* release_analyzer_data();
  
  // optional .ssl_decision_packet decision_data = 3;
  inline bool has_decision_data() const;
  inline void clear_decision_data();
  static const int kDecisionDataFieldNumber = 3;
  inline const ::ssl_decision_packet& decision_data() const;
  inline ::ssl_decision_packet* mutable_decision_data();
  inline ::ssl_decision_packet* release_decision_data();
  
  // optional .ssl_planner_packet planner_data = 4;
  inline bool has_planner_data() const;
  inline void clear_planner_data();
  static const int kPlannerDataFieldNumber = 4;
  inline const ::ssl_planner_packet& planner_data() const;
  inline ::ssl_planner_packet* mutable_planner_data();
  inline ::ssl_planner_packet* release_planner_data();
  
  // @@protoc_insertion_point(class_scope:ssl_visualizer_packet)
 private:
  inline void set_has_world_data();
  inline void clear_has_world_data();
  inline void set_has_analyzer_data();
  inline void clear_has_analyzer_data();
  inline void set_has_decision_data();
  inline void clear_has_decision_data();
  inline void set_has_planner_data();
  inline void clear_has_planner_data();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::ssl_world_packet* world_data_;
  ::ssl_analyzer_packet* analyzer_data_;
  ::ssl_decision_packet* decision_data_;
  ::ssl_planner_packet* planner_data_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(4 + 31) / 32];
  
  friend void  protobuf_AddDesc_ssl_5fvisualizer_2eproto();
  friend void protobuf_AssignDesc_ssl_5fvisualizer_2eproto();
  friend void protobuf_ShutdownFile_ssl_5fvisualizer_2eproto();
  
  void InitAsDefaultInstance();
  static ssl_visualizer_packet* default_instance_;
};
// ===================================================================


// ===================================================================

// ssl_visualizer_packet

// optional .ssl_world_packet world_data = 1;
inline bool ssl_visualizer_packet::has_world_data() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ssl_visualizer_packet::set_has_world_data() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ssl_visualizer_packet::clear_has_world_data() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ssl_visualizer_packet::clear_world_data() {
  if (world_data_ != NULL) world_data_->::ssl_world_packet::Clear();
  clear_has_world_data();
}
inline const ::ssl_world_packet& ssl_visualizer_packet::world_data() const {
  return world_data_ != NULL ? *world_data_ : *default_instance_->world_data_;
}
inline ::ssl_world_packet* ssl_visualizer_packet::mutable_world_data() {
  set_has_world_data();
  if (world_data_ == NULL) world_data_ = new ::ssl_world_packet;
  return world_data_;
}
inline ::ssl_world_packet* ssl_visualizer_packet::release_world_data() {
  clear_has_world_data();
  ::ssl_world_packet* temp = world_data_;
  world_data_ = NULL;
  return temp;
}

// optional .ssl_analyzer_packet analyzer_data = 2;
inline bool ssl_visualizer_packet::has_analyzer_data() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void ssl_visualizer_packet::set_has_analyzer_data() {
  _has_bits_[0] |= 0x00000002u;
}
inline void ssl_visualizer_packet::clear_has_analyzer_data() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void ssl_visualizer_packet::clear_analyzer_data() {
  if (analyzer_data_ != NULL) analyzer_data_->::ssl_analyzer_packet::Clear();
  clear_has_analyzer_data();
}
inline const ::ssl_analyzer_packet& ssl_visualizer_packet::analyzer_data() const {
  return analyzer_data_ != NULL ? *analyzer_data_ : *default_instance_->analyzer_data_;
}
inline ::ssl_analyzer_packet* ssl_visualizer_packet::mutable_analyzer_data() {
  set_has_analyzer_data();
  if (analyzer_data_ == NULL) analyzer_data_ = new ::ssl_analyzer_packet;
  return analyzer_data_;
}
inline ::ssl_analyzer_packet* ssl_visualizer_packet::release_analyzer_data() {
  clear_has_analyzer_data();
  ::ssl_analyzer_packet* temp = analyzer_data_;
  analyzer_data_ = NULL;
  return temp;
}

// optional .ssl_decision_packet decision_data = 3;
inline bool ssl_visualizer_packet::has_decision_data() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void ssl_visualizer_packet::set_has_decision_data() {
  _has_bits_[0] |= 0x00000004u;
}
inline void ssl_visualizer_packet::clear_has_decision_data() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void ssl_visualizer_packet::clear_decision_data() {
  if (decision_data_ != NULL) decision_data_->::ssl_decision_packet::Clear();
  clear_has_decision_data();
}
inline const ::ssl_decision_packet& ssl_visualizer_packet::decision_data() const {
  return decision_data_ != NULL ? *decision_data_ : *default_instance_->decision_data_;
}
inline ::ssl_decision_packet* ssl_visualizer_packet::mutable_decision_data() {
  set_has_decision_data();
  if (decision_data_ == NULL) decision_data_ = new ::ssl_decision_packet;
  return decision_data_;
}
inline ::ssl_decision_packet* ssl_visualizer_packet::release_decision_data() {
  clear_has_decision_data();
  ::ssl_decision_packet* temp = decision_data_;
  decision_data_ = NULL;
  return temp;
}

// optional .ssl_planner_packet planner_data = 4;
inline bool ssl_visualizer_packet::has_planner_data() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void ssl_visualizer_packet::set_has_planner_data() {
  _has_bits_[0] |= 0x00000008u;
}
inline void ssl_visualizer_packet::clear_has_planner_data() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void ssl_visualizer_packet::clear_planner_data() {
  if (planner_data_ != NULL) planner_data_->::ssl_planner_packet::Clear();
  clear_has_planner_data();
}
inline const ::ssl_planner_packet& ssl_visualizer_packet::planner_data() const {
  return planner_data_ != NULL ? *planner_data_ : *default_instance_->planner_data_;
}
inline ::ssl_planner_packet* ssl_visualizer_packet::mutable_planner_data() {
  set_has_planner_data();
  if (planner_data_ == NULL) planner_data_ = new ::ssl_planner_packet;
  return planner_data_;
}
inline ::ssl_planner_packet* ssl_visualizer_packet::release_planner_data() {
  clear_has_planner_data();
  ::ssl_planner_packet* temp = planner_data_;
  planner_data_ = NULL;
  return temp;
}


// @@protoc_insertion_point(namespace_scope)

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_ssl_5fvisualizer_2eproto__INCLUDED
