#pragma once

class font_metrics {
public:
  static font_metrics& instance();

  void initialise(const char* face, int size, int weight, bool italic, int char_set);

  int dip_to_dlu_x(float x) const;
  int dip_to_dlu_y(float y) const;

  float dlu_to_dip_x(int x) const;
  float dlu_to_dip_y(int y) const;

private:
  int base_unit_x_{};
  int base_unit_y_{};
};
