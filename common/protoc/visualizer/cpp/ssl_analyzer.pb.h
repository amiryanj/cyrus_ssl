// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ssl_analyzer.proto

#ifndef PROTOBUF_ssl_5fanalyzer_2eproto__INCLUDED
#define PROTOBUF_ssl_5fanalyzer_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2004000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2004001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_message_reflection.h>
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_ssl_5fanalyzer_2eproto();
void protobuf_AssignDesc_ssl_5fanalyzer_2eproto();
void protobuf_ShutdownFile_ssl_5fanalyzer_2eproto();

class ssl_analyzer_packet;
class ssl_analyzer_packet_RobotIntersectTime;

enum ssl_analyzer_packet_Color {
  ssl_analyzer_packet_Color_none = -1,
  ssl_analyzer_packet_Color_yellow = 0,
  ssl_analyzer_packet_Color_blue = 1
};
bool ssl_analyzer_packet_Color_IsValid(int value);
const ssl_analyzer_packet_Color ssl_analyzer_packet_Color_Color_MIN = ssl_analyzer_packet_Color_none;
const ssl_analyzer_packet_Color ssl_analyzer_packet_Color_Color_MAX = ssl_analyzer_packet_Color_blue;
const int ssl_analyzer_packet_Color_Color_ARRAYSIZE = ssl_analyzer_packet_Color_Color_MAX + 1;

const ::google::protobuf::EnumDescriptor* ssl_analyzer_packet_Color_descriptor();
inline const ::std::string& ssl_analyzer_packet_Color_Name(ssl_analyzer_packet_Color value) {
  return ::google::protobuf::internal::NameOfEnum(
    ssl_analyzer_packet_Color_descriptor(), value);
}
inline bool ssl_analyzer_packet_Color_Parse(
    const ::std::string& name, ssl_analyzer_packet_Color* value) {
  return ::google::protobuf::internal::ParseNamedEnum<ssl_analyzer_packet_Color>(
    ssl_analyzer_packet_Color_descriptor(), name, value);
}
// ===================================================================

class ssl_analyzer_packet_RobotIntersectTime : public ::google::protobuf::Message {
 public:
  ssl_analyzer_packet_RobotIntersectTime();
  virtual ~ssl_analyzer_packet_RobotIntersectTime();
  
  ssl_analyzer_packet_RobotIntersectTime(const ssl_analyzer_packet_RobotIntersectTime& from);
  
  inline ssl_analyzer_packet_RobotIntersectTime& operator=(const ssl_analyzer_packet_RobotIntersectTime& from) {
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
  static const ssl_analyzer_packet_RobotIntersectTime& default_instance();
  
  void Swap(ssl_analyzer_packet_RobotIntersectTime* other);
  
  // implements Message ----------------------------------------------
  
  ssl_analyzer_packet_RobotIntersectTime* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ssl_analyzer_packet_RobotIntersectTime& from);
  void MergeFrom(const ssl_analyzer_packet_RobotIntersectTime& from);
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
  
  // required .ssl_analyzer_packet.Color color = 1;
  inline bool has_color() const;
  inline void clear_color();
  static const int kColorFieldNumber = 1;
  inline ::ssl_analyzer_packet_Color color() const;
  inline void set_color(::ssl_analyzer_packet_Color value);
  
  // required uint32 id = 2;
  inline bool has_id() const;
  inline void clear_id();
  static const int kIdFieldNumber = 2;
  inline ::google::protobuf::uint32 id() const;
  inline void set_id(::google::protobuf::uint32 value);
  
  // required float time = 3;
  inline bool has_time() const;
  inline void clear_time();
  static const int kTimeFieldNumber = 3;
  inline float time() const;
  inline void set_time(float value);
  
  // required float intersect_x = 4;
  inline bool has_intersect_x() const;
  inline void clear_intersect_x();
  static const int kIntersectXFieldNumber = 4;
  inline float intersect_x() const;
  inline void set_intersect_x(float value);
  
  // required float intersect_y = 5;
  inline bool has_intersect_y() const;
  inline void clear_intersect_y();
  static const int kIntersectYFieldNumber = 5;
  inline float intersect_y() const;
  inline void set_intersect_y(float value);
  
  // @@protoc_insertion_point(class_scope:ssl_analyzer_packet.RobotIntersectTime)
 private:
  inline void set_has_color();
  inline void clear_has_color();
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_time();
  inline void clear_has_time();
  inline void set_has_intersect_x();
  inline void clear_has_intersect_x();
  inline void set_has_intersect_y();
  inline void clear_has_intersect_y();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  int color_;
  ::google::protobuf::uint32 id_;
  float time_;
  float intersect_x_;
  float intersect_y_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(5 + 31) / 32];
  
  friend void  protobuf_AddDesc_ssl_5fanalyzer_2eproto();
  friend void protobuf_AssignDesc_ssl_5fanalyzer_2eproto();
  friend void protobuf_ShutdownFile_ssl_5fanalyzer_2eproto();
  
  void InitAsDefaultInstance();
  static ssl_analyzer_packet_RobotIntersectTime* default_instance_;
};
// -------------------------------------------------------------------

class ssl_analyzer_packet : public ::google::protobuf::Message {
 public:
  ssl_analyzer_packet();
  virtual ~ssl_analyzer_packet();
  
  ssl_analyzer_packet(const ssl_analyzer_packet& from);
  
  inline ssl_analyzer_packet& operator=(const ssl_analyzer_packet& from) {
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
  static const ssl_analyzer_packet& default_instance();
  
  void Swap(ssl_analyzer_packet* other);
  
  // implements Message ----------------------------------------------
  
  ssl_analyzer_packet* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ssl_analyzer_packet& from);
  void MergeFrom(const ssl_analyzer_packet& from);
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
  
  typedef ssl_analyzer_packet_RobotIntersectTime RobotIntersectTime;
  
  typedef ssl_analyzer_packet_Color Color;
  static const Color none = ssl_analyzer_packet_Color_none;
  static const Color yellow = ssl_analyzer_packet_Color_yellow;
  static const Color blue = ssl_analyzer_packet_Color_blue;
  static inline bool Color_IsValid(int value) {
    return ssl_analyzer_packet_Color_IsValid(value);
  }
  static const Color Color_MIN =
    ssl_analyzer_packet_Color_Color_MIN;
  static const Color Color_MAX =
    ssl_analyzer_packet_Color_Color_MAX;
  static const int Color_ARRAYSIZE =
    ssl_analyzer_packet_Color_Color_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  Color_descriptor() {
    return ssl_analyzer_packet_Color_descriptor();
  }
  static inline const ::std::string& Color_Name(Color value) {
    return ssl_analyzer_packet_Color_Name(value);
  }
  static inline bool Color_Parse(const ::std::string& name,
      Color* value) {
    return ssl_analyzer_packet_Color_Parse(name, value);
  }
  
  // accessors -------------------------------------------------------
  
  // required uint32 nearest_blue_id = 1;
  inline bool has_nearest_blue_id() const;
  inline void clear_nearest_blue_id();
  static const int kNearestBlueIdFieldNumber = 1;
  inline ::google::protobuf::uint32 nearest_blue_id() const;
  inline void set_nearest_blue_id(::google::protobuf::uint32 value);
  
  // required uint32 nearest_yellow_id = 2;
  inline bool has_nearest_yellow_id() const;
  inline void clear_nearest_yellow_id();
  static const int kNearestYellowIdFieldNumber = 2;
  inline ::google::protobuf::uint32 nearest_yellow_id() const;
  inline void set_nearest_yellow_id(::google::protobuf::uint32 value);
  
  // required .ssl_analyzer_packet.Color possessor_team = 3;
  inline bool has_possessor_team() const;
  inline void clear_possessor_team();
  static const int kPossessorTeamFieldNumber = 3;
  inline ::ssl_analyzer_packet_Color possessor_team() const;
  inline void set_possessor_team(::ssl_analyzer_packet_Color value);
  
  // required bool nearest_can_kick = 4;
  inline bool has_nearest_can_kick() const;
  inline void clear_nearest_can_kick();
  static const int kNearestCanKickFieldNumber = 4;
  inline bool nearest_can_kick() const;
  inline void set_nearest_can_kick(bool value);
  
  // required bool is_game_running = 5;
  inline bool has_is_game_running() const;
  inline void clear_is_game_running();
  static const int kIsGameRunningFieldNumber = 5;
  inline bool is_game_running() const;
  inline void set_is_game_running(bool value);
  
  // repeated .ssl_analyzer_packet.RobotIntersectTime intersects = 6;
  inline int intersects_size() const;
  inline void clear_intersects();
  static const int kIntersectsFieldNumber = 6;
  inline const ::ssl_analyzer_packet_RobotIntersectTime& intersects(int index) const;
  inline ::ssl_analyzer_packet_RobotIntersectTime* mutable_intersects(int index);
  inline ::ssl_analyzer_packet_RobotIntersectTime* add_intersects();
  inline const ::google::protobuf::RepeatedPtrField< ::ssl_analyzer_packet_RobotIntersectTime >&
      intersects() const;
  inline ::google::protobuf::RepeatedPtrField< ::ssl_analyzer_packet_RobotIntersectTime >*
      mutable_intersects();
  
  // optional string comment = 7;
  inline bool has_comment() const;
  inline void clear_comment();
  static const int kCommentFieldNumber = 7;
  inline const ::std::string& comment() const;
  inline void set_comment(const ::std::string& value);
  inline void set_comment(const char* value);
  inline void set_comment(const char* value, size_t size);
  inline ::std::string* mutable_comment();
  inline ::std::string* release_comment();
  
  // @@protoc_insertion_point(class_scope:ssl_analyzer_packet)
 private:
  inline void set_has_nearest_blue_id();
  inline void clear_has_nearest_blue_id();
  inline void set_has_nearest_yellow_id();
  inline void clear_has_nearest_yellow_id();
  inline void set_has_possessor_team();
  inline void clear_has_possessor_team();
  inline void set_has_nearest_can_kick();
  inline void clear_has_nearest_can_kick();
  inline void set_has_is_game_running();
  inline void clear_has_is_game_running();
  inline void set_has_comment();
  inline void clear_has_comment();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::uint32 nearest_blue_id_;
  ::google::protobuf::uint32 nearest_yellow_id_;
  int possessor_team_;
  bool nearest_can_kick_;
  bool is_game_running_;
  ::google::protobuf::RepeatedPtrField< ::ssl_analyzer_packet_RobotIntersectTime > intersects_;
  ::std::string* comment_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(7 + 31) / 32];
  
  friend void  protobuf_AddDesc_ssl_5fanalyzer_2eproto();
  friend void protobuf_AssignDesc_ssl_5fanalyzer_2eproto();
  friend void protobuf_ShutdownFile_ssl_5fanalyzer_2eproto();
  
  void InitAsDefaultInstance();
  static ssl_analyzer_packet* default_instance_;
};
// ===================================================================


// ===================================================================

// ssl_analyzer_packet_RobotIntersectTime

// required .ssl_analyzer_packet.Color color = 1;
inline bool ssl_analyzer_packet_RobotIntersectTime::has_color() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ssl_analyzer_packet_RobotIntersectTime::set_has_color() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ssl_analyzer_packet_RobotIntersectTime::clear_has_color() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ssl_analyzer_packet_RobotIntersectTime::clear_color() {
  color_ = -1;
  clear_has_color();
}
inline ::ssl_analyzer_packet_Color ssl_analyzer_packet_RobotIntersectTime::color() const {
  return static_cast< ::ssl_analyzer_packet_Color >(color_);
}
inline void ssl_analyzer_packet_RobotIntersectTime::set_color(::ssl_analyzer_packet_Color value) {
  GOOGLE_DCHECK(::ssl_analyzer_packet_Color_IsValid(value));
  set_has_color();
  color_ = value;
}

// required uint32 id = 2;
inline bool ssl_analyzer_packet_RobotIntersectTime::has_id() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void ssl_analyzer_packet_RobotIntersectTime::set_has_id() {
  _has_bits_[0] |= 0x00000002u;
}
inline void ssl_analyzer_packet_RobotIntersectTime::clear_has_id() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void ssl_analyzer_packet_RobotIntersectTime::clear_id() {
  id_ = 0u;
  clear_has_id();
}
inline ::google::protobuf::uint32 ssl_analyzer_packet_RobotIntersectTime::id() const {
  return id_;
}
inline void ssl_analyzer_packet_RobotIntersectTime::set_id(::google::protobuf::uint32 value) {
  set_has_id();
  id_ = value;
}

// required float time = 3;
inline bool ssl_analyzer_packet_RobotIntersectTime::has_time() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void ssl_analyzer_packet_RobotIntersectTime::set_has_time() {
  _has_bits_[0] |= 0x00000004u;
}
inline void ssl_analyzer_packet_RobotIntersectTime::clear_has_time() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void ssl_analyzer_packet_RobotIntersectTime::clear_time() {
  time_ = 0;
  clear_has_time();
}
inline float ssl_analyzer_packet_RobotIntersectTime::time() const {
  return time_;
}
inline void ssl_analyzer_packet_RobotIntersectTime::set_time(float value) {
  set_has_time();
  time_ = value;
}

// required float intersect_x = 4;
inline bool ssl_analyzer_packet_RobotIntersectTime::has_intersect_x() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void ssl_analyzer_packet_RobotIntersectTime::set_has_intersect_x() {
  _has_bits_[0] |= 0x00000008u;
}
inline void ssl_analyzer_packet_RobotIntersectTime::clear_has_intersect_x() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void ssl_analyzer_packet_RobotIntersectTime::clear_intersect_x() {
  intersect_x_ = 0;
  clear_has_intersect_x();
}
inline float ssl_analyzer_packet_RobotIntersectTime::intersect_x() const {
  return intersect_x_;
}
inline void ssl_analyzer_packet_RobotIntersectTime::set_intersect_x(float value) {
  set_has_intersect_x();
  intersect_x_ = value;
}

// required float intersect_y = 5;
inline bool ssl_analyzer_packet_RobotIntersectTime::has_intersect_y() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void ssl_analyzer_packet_RobotIntersectTime::set_has_intersect_y() {
  _has_bits_[0] |= 0x00000010u;
}
inline void ssl_analyzer_packet_RobotIntersectTime::clear_has_intersect_y() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void ssl_analyzer_packet_RobotIntersectTime::clear_intersect_y() {
  intersect_y_ = 0;
  clear_has_intersect_y();
}
inline float ssl_analyzer_packet_RobotIntersectTime::intersect_y() const {
  return intersect_y_;
}
inline void ssl_analyzer_packet_RobotIntersectTime::set_intersect_y(float value) {
  set_has_intersect_y();
  intersect_y_ = value;
}

// -------------------------------------------------------------------

// ssl_analyzer_packet

// required uint32 nearest_blue_id = 1;
inline bool ssl_analyzer_packet::has_nearest_blue_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ssl_analyzer_packet::set_has_nearest_blue_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ssl_analyzer_packet::clear_has_nearest_blue_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ssl_analyzer_packet::clear_nearest_blue_id() {
  nearest_blue_id_ = 0u;
  clear_has_nearest_blue_id();
}
inline ::google::protobuf::uint32 ssl_analyzer_packet::nearest_blue_id() const {
  return nearest_blue_id_;
}
inline void ssl_analyzer_packet::set_nearest_blue_id(::google::protobuf::uint32 value) {
  set_has_nearest_blue_id();
  nearest_blue_id_ = value;
}

// required uint32 nearest_yellow_id = 2;
inline bool ssl_analyzer_packet::has_nearest_yellow_id() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void ssl_analyzer_packet::set_has_nearest_yellow_id() {
  _has_bits_[0] |= 0x00000002u;
}
inline void ssl_analyzer_packet::clear_has_nearest_yellow_id() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void ssl_analyzer_packet::clear_nearest_yellow_id() {
  nearest_yellow_id_ = 0u;
  clear_has_nearest_yellow_id();
}
inline ::google::protobuf::uint32 ssl_analyzer_packet::nearest_yellow_id() const {
  return nearest_yellow_id_;
}
inline void ssl_analyzer_packet::set_nearest_yellow_id(::google::protobuf::uint32 value) {
  set_has_nearest_yellow_id();
  nearest_yellow_id_ = value;
}

// required .ssl_analyzer_packet.Color possessor_team = 3;
inline bool ssl_analyzer_packet::has_possessor_team() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void ssl_analyzer_packet::set_has_possessor_team() {
  _has_bits_[0] |= 0x00000004u;
}
inline void ssl_analyzer_packet::clear_has_possessor_team() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void ssl_analyzer_packet::clear_possessor_team() {
  possessor_team_ = -1;
  clear_has_possessor_team();
}
inline ::ssl_analyzer_packet_Color ssl_analyzer_packet::possessor_team() const {
  return static_cast< ::ssl_analyzer_packet_Color >(possessor_team_);
}
inline void ssl_analyzer_packet::set_possessor_team(::ssl_analyzer_packet_Color value) {
  GOOGLE_DCHECK(::ssl_analyzer_packet_Color_IsValid(value));
  set_has_possessor_team();
  possessor_team_ = value;
}

// required bool nearest_can_kick = 4;
inline bool ssl_analyzer_packet::has_nearest_can_kick() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void ssl_analyzer_packet::set_has_nearest_can_kick() {
  _has_bits_[0] |= 0x00000008u;
}
inline void ssl_analyzer_packet::clear_has_nearest_can_kick() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void ssl_analyzer_packet::clear_nearest_can_kick() {
  nearest_can_kick_ = false;
  clear_has_nearest_can_kick();
}
inline bool ssl_analyzer_packet::nearest_can_kick() const {
  return nearest_can_kick_;
}
inline void ssl_analyzer_packet::set_nearest_can_kick(bool value) {
  set_has_nearest_can_kick();
  nearest_can_kick_ = value;
}

// required bool is_game_running = 5;
inline bool ssl_analyzer_packet::has_is_game_running() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void ssl_analyzer_packet::set_has_is_game_running() {
  _has_bits_[0] |= 0x00000010u;
}
inline void ssl_analyzer_packet::clear_has_is_game_running() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void ssl_analyzer_packet::clear_is_game_running() {
  is_game_running_ = false;
  clear_has_is_game_running();
}
inline bool ssl_analyzer_packet::is_game_running() const {
  return is_game_running_;
}
inline void ssl_analyzer_packet::set_is_game_running(bool value) {
  set_has_is_game_running();
  is_game_running_ = value;
}

// repeated .ssl_analyzer_packet.RobotIntersectTime intersects = 6;
inline int ssl_analyzer_packet::intersects_size() const {
  return intersects_.size();
}
inline void ssl_analyzer_packet::clear_intersects() {
  intersects_.Clear();
}
inline const ::ssl_analyzer_packet_RobotIntersectTime& ssl_analyzer_packet::intersects(int index) const {
  return intersects_.Get(index);
}
inline ::ssl_analyzer_packet_RobotIntersectTime* ssl_analyzer_packet::mutable_intersects(int index) {
  return intersects_.Mutable(index);
}
inline ::ssl_analyzer_packet_RobotIntersectTime* ssl_analyzer_packet::add_intersects() {
  return intersects_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::ssl_analyzer_packet_RobotIntersectTime >&
ssl_analyzer_packet::intersects() const {
  return intersects_;
}
inline ::google::protobuf::RepeatedPtrField< ::ssl_analyzer_packet_RobotIntersectTime >*
ssl_analyzer_packet::mutable_intersects() {
  return &intersects_;
}

// optional string comment = 7;
inline bool ssl_analyzer_packet::has_comment() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
inline void ssl_analyzer_packet::set_has_comment() {
  _has_bits_[0] |= 0x00000040u;
}
inline void ssl_analyzer_packet::clear_has_comment() {
  _has_bits_[0] &= ~0x00000040u;
}
inline void ssl_analyzer_packet::clear_comment() {
  if (comment_ != &::google::protobuf::internal::kEmptyString) {
    comment_->clear();
  }
  clear_has_comment();
}
inline const ::std::string& ssl_analyzer_packet::comment() const {
  return *comment_;
}
inline void ssl_analyzer_packet::set_comment(const ::std::string& value) {
  set_has_comment();
  if (comment_ == &::google::protobuf::internal::kEmptyString) {
    comment_ = new ::std::string;
  }
  comment_->assign(value);
}
inline void ssl_analyzer_packet::set_comment(const char* value) {
  set_has_comment();
  if (comment_ == &::google::protobuf::internal::kEmptyString) {
    comment_ = new ::std::string;
  }
  comment_->assign(value);
}
inline void ssl_analyzer_packet::set_comment(const char* value, size_t size) {
  set_has_comment();
  if (comment_ == &::google::protobuf::internal::kEmptyString) {
    comment_ = new ::std::string;
  }
  comment_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* ssl_analyzer_packet::mutable_comment() {
  set_has_comment();
  if (comment_ == &::google::protobuf::internal::kEmptyString) {
    comment_ = new ::std::string;
  }
  return comment_;
}
inline ::std::string* ssl_analyzer_packet::release_comment() {
  clear_has_comment();
  if (comment_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = comment_;
    comment_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}


// @@protoc_insertion_point(namespace_scope)

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::ssl_analyzer_packet_Color>() {
  return ::ssl_analyzer_packet_Color_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_ssl_5fanalyzer_2eproto__INCLUDED