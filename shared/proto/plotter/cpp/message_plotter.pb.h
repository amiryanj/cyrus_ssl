// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: message_plotter.proto

#ifndef PROTOBUF_message_5fplotter_2eproto__INCLUDED
#define PROTOBUF_message_5fplotter_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2005000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_message_5fplotter_2eproto();
void protobuf_AssignDesc_message_5fplotter_2eproto();
void protobuf_ShutdownFile_message_5fplotter_2eproto();

class Plotter_Packet;

// ===================================================================

class Plotter_Packet : public ::google::protobuf::Message {
 public:
  Plotter_Packet();
  virtual ~Plotter_Packet();

  Plotter_Packet(const Plotter_Packet& from);

  inline Plotter_Packet& operator=(const Plotter_Packet& from) {
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
  static const Plotter_Packet& default_instance();

  void Swap(Plotter_Packet* other);

  // implements Message ----------------------------------------------

  Plotter_Packet* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Plotter_Packet& from);
  void MergeFrom(const Plotter_Packet& from);
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

  // required string name = 1;
  inline bool has_name() const;
  inline void clear_name();
  static const int kNameFieldNumber = 1;
  inline const ::std::string& name() const;
  inline void set_name(const ::std::string& value);
  inline void set_name(const char* value);
  inline void set_name(const char* value, size_t size);
  inline ::std::string* mutable_name();
  inline ::std::string* release_name();
  inline void set_allocated_name(::std::string* name);

  // repeated double values = 2;
  inline int values_size() const;
  inline void clear_values();
  static const int kValuesFieldNumber = 2;
  inline double values(int index) const;
  inline void set_values(int index, double value);
  inline void add_values(double value);
  inline const ::google::protobuf::RepeatedField< double >&
      values() const;
  inline ::google::protobuf::RepeatedField< double >*
      mutable_values();

  // optional double key = 3;
  inline bool has_key() const;
  inline void clear_key();
  static const int kKeyFieldNumber = 3;
  inline double key() const;
  inline void set_key(double value);

  // repeated string legends = 4;
  inline int legends_size() const;
  inline void clear_legends();
  static const int kLegendsFieldNumber = 4;
  inline const ::std::string& legends(int index) const;
  inline ::std::string* mutable_legends(int index);
  inline void set_legends(int index, const ::std::string& value);
  inline void set_legends(int index, const char* value);
  inline void set_legends(int index, const char* value, size_t size);
  inline ::std::string* add_legends();
  inline void add_legends(const ::std::string& value);
  inline void add_legends(const char* value);
  inline void add_legends(const char* value, size_t size);
  inline const ::google::protobuf::RepeatedPtrField< ::std::string>& legends() const;
  inline ::google::protobuf::RepeatedPtrField< ::std::string>* mutable_legends();

  // optional bool clear_history = 5;
  inline bool has_clear_history() const;
  inline void clear_clear_history();
  static const int kClearHistoryFieldNumber = 5;
  inline bool clear_history() const;
  inline void set_clear_history(bool value);

  // optional string sender_name = 6;
  inline bool has_sender_name() const;
  inline void clear_sender_name();
  static const int kSenderNameFieldNumber = 6;
  inline const ::std::string& sender_name() const;
  inline void set_sender_name(const ::std::string& value);
  inline void set_sender_name(const char* value);
  inline void set_sender_name(const char* value, size_t size);
  inline ::std::string* mutable_sender_name();
  inline ::std::string* release_sender_name();
  inline void set_allocated_sender_name(::std::string* sender_name);

  // @@protoc_insertion_point(class_scope:Plotter_Packet)
 private:
  inline void set_has_name();
  inline void clear_has_name();
  inline void set_has_key();
  inline void clear_has_key();
  inline void set_has_clear_history();
  inline void clear_has_clear_history();
  inline void set_has_sender_name();
  inline void clear_has_sender_name();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::std::string* name_;
  ::google::protobuf::RepeatedField< double > values_;
  double key_;
  ::google::protobuf::RepeatedPtrField< ::std::string> legends_;
  ::std::string* sender_name_;
  bool clear_history_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(6 + 31) / 32];

  friend void  protobuf_AddDesc_message_5fplotter_2eproto();
  friend void protobuf_AssignDesc_message_5fplotter_2eproto();
  friend void protobuf_ShutdownFile_message_5fplotter_2eproto();

  void InitAsDefaultInstance();
  static Plotter_Packet* default_instance_;
};
// ===================================================================


// ===================================================================

// Plotter_Packet

// required string name = 1;
inline bool Plotter_Packet::has_name() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Plotter_Packet::set_has_name() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Plotter_Packet::clear_has_name() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Plotter_Packet::clear_name() {
  if (name_ != &::google::protobuf::internal::kEmptyString) {
    name_->clear();
  }
  clear_has_name();
}
inline const ::std::string& Plotter_Packet::name() const {
  return *name_;
}
inline void Plotter_Packet::set_name(const ::std::string& value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline void Plotter_Packet::set_name(const char* value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline void Plotter_Packet::set_name(const char* value, size_t size) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Plotter_Packet::mutable_name() {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  return name_;
}
inline ::std::string* Plotter_Packet::release_name() {
  clear_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = name_;
    name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void Plotter_Packet::set_allocated_name(::std::string* name) {
  if (name_ != &::google::protobuf::internal::kEmptyString) {
    delete name_;
  }
  if (name) {
    set_has_name();
    name_ = name;
  } else {
    clear_has_name();
    name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// repeated double values = 2;
inline int Plotter_Packet::values_size() const {
  return values_.size();
}
inline void Plotter_Packet::clear_values() {
  values_.Clear();
}
inline double Plotter_Packet::values(int index) const {
  return values_.Get(index);
}
inline void Plotter_Packet::set_values(int index, double value) {
  values_.Set(index, value);
}
inline void Plotter_Packet::add_values(double value) {
  values_.Add(value);
}
inline const ::google::protobuf::RepeatedField< double >&
Plotter_Packet::values() const {
  return values_;
}
inline ::google::protobuf::RepeatedField< double >*
Plotter_Packet::mutable_values() {
  return &values_;
}

// optional double key = 3;
inline bool Plotter_Packet::has_key() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void Plotter_Packet::set_has_key() {
  _has_bits_[0] |= 0x00000004u;
}
inline void Plotter_Packet::clear_has_key() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void Plotter_Packet::clear_key() {
  key_ = 0;
  clear_has_key();
}
inline double Plotter_Packet::key() const {
  return key_;
}
inline void Plotter_Packet::set_key(double value) {
  set_has_key();
  key_ = value;
}

// repeated string legends = 4;
inline int Plotter_Packet::legends_size() const {
  return legends_.size();
}
inline void Plotter_Packet::clear_legends() {
  legends_.Clear();
}
inline const ::std::string& Plotter_Packet::legends(int index) const {
  return legends_.Get(index);
}
inline ::std::string* Plotter_Packet::mutable_legends(int index) {
  return legends_.Mutable(index);
}
inline void Plotter_Packet::set_legends(int index, const ::std::string& value) {
  legends_.Mutable(index)->assign(value);
}
inline void Plotter_Packet::set_legends(int index, const char* value) {
  legends_.Mutable(index)->assign(value);
}
inline void Plotter_Packet::set_legends(int index, const char* value, size_t size) {
  legends_.Mutable(index)->assign(
    reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Plotter_Packet::add_legends() {
  return legends_.Add();
}
inline void Plotter_Packet::add_legends(const ::std::string& value) {
  legends_.Add()->assign(value);
}
inline void Plotter_Packet::add_legends(const char* value) {
  legends_.Add()->assign(value);
}
inline void Plotter_Packet::add_legends(const char* value, size_t size) {
  legends_.Add()->assign(reinterpret_cast<const char*>(value), size);
}
inline const ::google::protobuf::RepeatedPtrField< ::std::string>&
Plotter_Packet::legends() const {
  return legends_;
}
inline ::google::protobuf::RepeatedPtrField< ::std::string>*
Plotter_Packet::mutable_legends() {
  return &legends_;
}

// optional bool clear_history = 5;
inline bool Plotter_Packet::has_clear_history() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void Plotter_Packet::set_has_clear_history() {
  _has_bits_[0] |= 0x00000010u;
}
inline void Plotter_Packet::clear_has_clear_history() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void Plotter_Packet::clear_clear_history() {
  clear_history_ = false;
  clear_has_clear_history();
}
inline bool Plotter_Packet::clear_history() const {
  return clear_history_;
}
inline void Plotter_Packet::set_clear_history(bool value) {
  set_has_clear_history();
  clear_history_ = value;
}

// optional string sender_name = 6;
inline bool Plotter_Packet::has_sender_name() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void Plotter_Packet::set_has_sender_name() {
  _has_bits_[0] |= 0x00000020u;
}
inline void Plotter_Packet::clear_has_sender_name() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void Plotter_Packet::clear_sender_name() {
  if (sender_name_ != &::google::protobuf::internal::kEmptyString) {
    sender_name_->clear();
  }
  clear_has_sender_name();
}
inline const ::std::string& Plotter_Packet::sender_name() const {
  return *sender_name_;
}
inline void Plotter_Packet::set_sender_name(const ::std::string& value) {
  set_has_sender_name();
  if (sender_name_ == &::google::protobuf::internal::kEmptyString) {
    sender_name_ = new ::std::string;
  }
  sender_name_->assign(value);
}
inline void Plotter_Packet::set_sender_name(const char* value) {
  set_has_sender_name();
  if (sender_name_ == &::google::protobuf::internal::kEmptyString) {
    sender_name_ = new ::std::string;
  }
  sender_name_->assign(value);
}
inline void Plotter_Packet::set_sender_name(const char* value, size_t size) {
  set_has_sender_name();
  if (sender_name_ == &::google::protobuf::internal::kEmptyString) {
    sender_name_ = new ::std::string;
  }
  sender_name_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Plotter_Packet::mutable_sender_name() {
  set_has_sender_name();
  if (sender_name_ == &::google::protobuf::internal::kEmptyString) {
    sender_name_ = new ::std::string;
  }
  return sender_name_;
}
inline ::std::string* Plotter_Packet::release_sender_name() {
  clear_has_sender_name();
  if (sender_name_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = sender_name_;
    sender_name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void Plotter_Packet::set_allocated_sender_name(::std::string* sender_name) {
  if (sender_name_ != &::google::protobuf::internal::kEmptyString) {
    delete sender_name_;
  }
  if (sender_name) {
    set_has_sender_name();
    sender_name_ = sender_name;
  } else {
    clear_has_sender_name();
    sender_name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}


// @@protoc_insertion_point(namespace_scope)

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_message_5fplotter_2eproto__INCLUDED
