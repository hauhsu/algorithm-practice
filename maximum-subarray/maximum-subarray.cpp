#include <climits>
#include <iostream>
#include <vector>
#include <utility> 

using namespace std;

vector<int> num_seq;

struct SubSeq
{
  int begin_idx;
  int end_idx;
  int summation;
};

void print_subseq(SubSeq subseq) {
  cout << "L: " << subseq.begin_idx << ", R: " << subseq.end_idx 
       << ", Sum: " << subseq.summation<< endl; 
}

SubSeq find_max_crossing_subarray(SubSeq sub_seq) {
  int mid_index = (sub_seq.begin_idx + sub_seq.end_idx)/2; 
  int max_index_left = mid_index;
  int left_sum = INT_MIN;
  int sum = 0;
  for (int i = mid_index; i >= sub_seq.begin_idx; --i) {
    sum = sum + num_seq[i];
    if (sum > left_sum) {
      left_sum = sum;
      max_index_left = i;
    }
  }

  int right_sum = INT_MIN;
  sum = 0;
  int max_index_right = mid_index;
  for (int i = mid_index+1; i <= sub_seq.end_idx; ++i) {
    sum = sum + num_seq[i];
    if (sum > right_sum) {
      right_sum = sum;
      max_index_right = i;
    }
  }

  return SubSeq{max_index_left, max_index_right, left_sum+right_sum};
}

SubSeq find_max_subarray(SubSeq sub_seq) {
  cout << "find_max_subarray: ";
  print_subseq(sub_seq);
  if (sub_seq.begin_idx == sub_seq.end_idx) {
    return SubSeq{sub_seq.begin_idx, sub_seq.end_idx, num_seq[sub_seq.begin_idx]};
  }

  else {
    int mid_index = (sub_seq.begin_idx + sub_seq.end_idx)/2; 
    SubSeq left_part {sub_seq.begin_idx, mid_index, 0};
    SubSeq left_max = find_max_subarray(left_part);
    cout << "max_left_subarray:";
    print_subseq(left_max);

    SubSeq right_part {mid_index+1, sub_seq.end_idx, 0};
    SubSeq right_max = find_max_subarray(right_part);
    cout << "max_right_subarray:";
    print_subseq(right_max);

    SubSeq max_cross_subarray;
    if (sub_seq.end_idx - sub_seq.begin_idx > 2) {
      max_cross_subarray = find_max_crossing_subarray(sub_seq);
      cout << "max_cross_subarray:";
      print_subseq(max_cross_subarray);
    }
    else {
      max_cross_subarray.summation = INT_MIN;
    }

    if (left_max.summation>= right_max.summation&& left_max.summation>= max_cross_subarray.summation) {
      return left_max;
    } else if (right_max.summation>= left_max.summation&& right_max.summation>= max_cross_subarray.summation) {
      return right_max;
    } else {
      return max_cross_subarray;
    }
  }
}

int main(int argc, char *argv[]) {

  num_seq = {0, 1, 2, -4, -2, 3, 5, 6, -1};
  SubSeq init_seq {0, static_cast<int>(num_seq.size()-1), 0};
  SubSeq max_subarray = find_max_subarray(init_seq);
  cout << "Left index: " << max_subarray.begin_idx << endl;
  cout << "Right index: " << max_subarray.end_idx << endl;
  cout << "Maximum: " << max_subarray.summation << endl;
  
  return 0;
}
