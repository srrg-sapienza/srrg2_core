#pragma once
#include "message_sink_base.h"

namespace srrg2_core {

  class MessageSynchronizedSink : public MessageSinkBase {
  public:
    PARAM(PropertyString, output_topic, "name of the topic in the message pack", "pack", 0);
    PARAM(PropertyString,
          output_frame_id,
          "name of the frame in the message pack",
          "pack_frame_id",
          0);
    PARAM_VECTOR(PropertyVector_<std::string>, topics, "topics to synchronize", &_topics_changed);
    PARAM(PropertyDouble,
          time_interval,
          "interval for the messages to be sinchronized",
          0.1,
          &_interval_changed);

    void resetCounters();

    bool putMessage(BaseSensorMessagePtr msg_) override;

    int numDroppedMessages() const {
      return _num_dropped_messages;
    }

    double dt() const {
      return _t_max - _t_min;
    }

    void reset() override;

  protected:
    void clearBuffer();
    void handleTopicsChanged();
    void handleIntervalChanged();
    bool isPacketReady();

    std::map<std::string, BaseSensorMessagePtr> _message_map;
    bool _topics_changed      = true;
    bool _interval_changed    = true;
    int _num_dropped_messages = 0;
    int _seq;
    double _t_min, _t_max;
  };

  using MessageSynchronizedSinkPtr = std::shared_ptr<MessageSynchronizedSink>;

} // namespace srrg2_core