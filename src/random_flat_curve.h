#ifndef RANDOM_FLAT_CURVE_H
#define RANDOM_FLAT_CURVE_H

#include <bn_algorithm.h>
#include <bn_log.h>
#include <bn_string.h>
#include <bn_vector.h>

#include "bn_fixed_fwd.h"
#include "utils.h"

typedef int T;

template <int steps> class RandomFlatCurve
{
  public:
    RandomFlatCurve(T max_input, T max_output)
    {
        generate_random_values<2 * steps>(_x_list, max_input);
        generate_random_values<steps>(_y_list, max_output);
        bn::sort(_x_list.begin(), _x_list.end());
        bn::sort(_y_list.begin(), _y_list.end());
    }

    T operator()(T t)
    {
        // find interval:
        if (_x_list[_last_kf] <= t && t < _x_list[_last_kf + 1])
        {
        }
        else
        {
            for (int i = 0; i < _x_list.size() - 1; ++i)
            {
                if (_x_list[i] <= t && t < _x_list[i + 1])
                {
                    _last_kf = i;
                    break;
                }
            }
        }
        if (_last_kf % 2 == 1) // flat
        {
            return _y_list[(_last_kf + 1) / 2];
        }

        int y_index = _last_kf / 2;
        return map(t, _x_list[_last_kf], _x_list[_last_kf + 1], _y_list[y_index], _y_list[y_index + 1]);
    }

  private:
    static int random_number(int max_value) { return randomizer.get_int(1, max_value); }

    static bn::fixed random_number(bn::fixed max_value)
    {
        while (true)
        {
            bn::fixed current = randomizer.get_fixed(max_value);
            if (current != 0.)
                return current;
        }
    }

    template <int nb> static void generate_random_values(typename bn::vector<T, nb + 2> &output, T max_value)
    {
        output.push_back(T(0));
        for (int iteration = 0; iteration < nb; ++iteration)
        {
            while (true)
            {
                T current = random_number(max_value);
                bool found_same = false;
                for (T elm : output)
                {
                    if (elm == current)
                    {
                        found_same = true;
                        break;
                    }
                }
                if (!found_same)
                {
                    output.push_back(current);
                    break;
                }
            }
        }
        output.push_back(max_value);
    }

    bn::vector<T, 2 * steps + 2> _x_list;
    bn::vector<T, steps + 2> _y_list;
    int _last_kf = 0;
};

#endif