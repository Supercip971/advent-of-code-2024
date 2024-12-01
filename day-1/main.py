

with open('input.txt') as f:
    
    # data is represented as a list of two integers
    

    first_array = []
    second_array = []
    for line in f.readlines(): 
        
        data = [int(x) for x in line.split()]
        if len(data) != 2:
            print("error in our data")
            break 
            
        first_array.append(data[0])
        second_array.append(data[1])
    
    print(first_array)
    print(second_array)

    first_array.sort()
    second_array.sort()

    delta_array = []
    for i in range(len(first_array)):
        delta_array.append(second_array[i] - first_array[i])
    
    summed = 0
    for i in range(len(delta_array)):
        summed += abs(delta_array[i])
    
    print(f'final result: {summed}')