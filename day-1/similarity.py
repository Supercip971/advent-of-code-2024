

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

    mapped_sum = {}

    for i in range(len(second_array)): 
        mapped_sum[second_array[i]] = 1 + mapped_sum.get(second_array[i], 0)
        
    summed = 0

    for i in range(len(first_array)):
        summed += first_array[i] * abs(mapped_sum.get(first_array[i], 0))
    
    print(f'final result: {summed}')