"""Demo showcase of some of the raw data"""

from myo_python.myo_python import *
from matplotlib import pyplot as plt
import os

grips_prefix = os.path.abspath(os.curdir) + '/raw_data/double_grips/'
loc_1_prefix = os.path.abspath(os.curdir) + '/raw_data/loc_1/'
loc_2_prefix = os.path.abspath(os.curdir) + '/raw_data/loc_2/'


f, (ax1, ax2, ax3) = plt.subplots(3, sharex=True)
first_results = parse_file(grips_prefix + 'double_grips_x9_1802192025.txt')
ax1.plot(first_results[:, 0], first_results[:, 1])
ax1.plot(first_results[:, 0], first_results[:, 2])
ax1.set_title('Quick succession grips')
ax1.set_ylim((0, 1023))

second_results = parse_file(loc_1_prefix + 'power_grips_x9_3secinter_1802191953.txt')
ax2.plot(second_results[:, 0], second_results[:, 1])
ax2.plot(second_results[:, 0], second_results[:, 2])
ax2.set_title('Location 1 power grips')
ax2.set_ylim((0, 1023))

third = parse_file(loc_2_prefix + 'power_grips_x9_3secinter_1802192003.txt')
ax3.plot(third[:, 0], third[:, 1])
ax3.plot(third[:, 0], third[:, 2])
ax3.set_ylim((0, 1023))

ax3.set_title('Location 2 power grips')

f.subplots_adjust(hspace=0.3)
ax3.set_xlabel('Time (ms)')
plt.show()
