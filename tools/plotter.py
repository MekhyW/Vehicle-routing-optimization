import os
import re
import matplotlib.pyplot as plt

def read_time_from_file(file_path):
    with open(file_path, 'r') as file:
        first_line = file.readline()
        match = re.match(r'Time taken by solver: (\d+) ms', first_line)
        if match:
            return int(match.group(1))
    return None

def get_values(folder_path):
    input_sizes = []
    times = []
    for file_name in os.listdir(folder_path):
        if file_name == '.gitignore':
            continue
        match = re.match(r'graph-(\d+)\.txt_output\.txt', file_name)
        if match:
            input_size = int(match.group(1))
            file_path = os.path.join(folder_path, file_name)
            time = read_time_from_file(file_path)
            if time is not None:
                input_sizes.append(input_size)
                times.append(time)
    return input_sizes, times

def plot_times(folder_path, label):
    input_sizes, times = get_values(folder_path)
    if input_sizes and times:
        plt.plot(input_sizes, times, label=label, color='blue', marker='o')
        plt.xlabel('Input Size')
        plt.ylabel('Time (ms)')
        plt.title('Time taken by solver vs Input Size')
        plt.legend()
        plt.show()
        plt.loglog(input_sizes, times, label=label, color='blue', marker='o')
        plt.xlabel('Input Size')
        plt.ylabel('Time (ms)')
        plt.title('Time taken by solver vs Input Size (logarithmic)')
        plt.legend()
        plt.show()
    else:
        print("No valid data found in the specified folder.")

def plot_times_logarithmic(folder_path, label):
    input_sizes, times = get_values(folder_path)

folder_path = 'output'
label = input("Enter label for graph: ")
plot_times(folder_path, label)
