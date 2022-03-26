from sseclient import SSEClient     # is a requirement
import matplotlib.pyplot as plt     # is a requirement
import json

messages = SSEClient('https://api.particle.io/v1/devices/e00fce68610702f7e28594a7/events?access_token=7994990de0b66cc2d0a1c07c59be506578c018bd')
cell_voltages = [[],[],[],[],[],[],[],[],[],[],[],[],[],[],[]]
colors = ['b','g','r','c','m','y','k','b--','g--','r--','c--','m--','y--','k--', 'b-+']
numbers = ['1', '2', '3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15']

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
        for i in range(0, 15):
            cell_voltages[i].append(float(split_data[i]))
            if float(split_data[i]) > 2:
                break_flag = True
                break
        if break_flag:
            break


        for i in range(0,15):
            plt.plot(cell_voltages[i], colors[i])
        
        plt.legend(numbers)
        print(data['data'])
        
        plt.pause(1)
    except:
        continue
    # print(data)

plt.show(block=True)
