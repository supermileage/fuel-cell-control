from sseclient import SSEClient     # is a requirement
import matplotlib.pyplot as plt     # is a requirement
import json

messages = SSEClient('https://api.particle.io/v1/devices/e00fce68610702f7e28594a7/events?access_token=2d4d4f761e9147ba236b8fb6460913469e492743')
cell_voltages = [[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[]]
colors = ['b','g','r','c','m','y','k','b--','g--','r--','c--','m--','y--','k--', 'b-+','g-+','r-+']
numbers = ['17', '16', '15', '14', '13', '12', '11', '10', '9', '8', '7', '6', '5', '4', '3', '2','1']
ymin=-0.5
ymax = 1.5
ax = plt.gca()
ax.set_ylim([ymin, ymax])

#fig, axs = plt.subplots(2)

for msg in messages:
    
    try:
        data = json.loads(msg.data)
    except:
        print("invalid data")
        print(msg.data)
        continue
    try:
        current_cell_voltages = []
        #print(data['data'])
        split_data = data['data'].split()
        break_flag = False
        for i in range(0, 17):
            cell_voltages[i].append(float(split_data[i]))


        for i in range(0,17):
            # plt.subplot(2, 1, 1)
            plt.figure(num=1)
            plt.plot(cell_voltages[i], colors[i])
            #axs[0, 0].plot(cell_voltages[i], colors[i])
        
        plt.legend(numbers)
        print(data['data'])
        
        plt.pause(1)
        # total_v = float(split_data[17 + 6 - 1])
        # print(total_v)

        ## plt.subplot(2, 1, 2)
        # plt.figure(num=2)
        # plt.plot(total_v,colors[0])
        # plt.pause(1)
    except:
        continue
    # print(data)

plt.show(block=True)
