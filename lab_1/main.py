from iarray import *

def test_1():
  arr = list()
  
  arr.append(0)
  arr.append(-1)
  arr.append(3)
  arr.append(-2)
  arr.append(5)
  
  return arr, 5

def test_2():
  arr = list()
  
  arr.append(0)
  arr.append(-1)
  arr.append(3)
  arr.append(-2)
  arr.append(-2)
  
  return arr, 5

def main():
  arr, n = test_1()

  print("Source")
  print_array(arr, n)
  
  new_arr, new_n = form_array(arr, n)

  print("Result")
  print_array(new_arr, new_n)
  
  arr, n = test_2()
  print("Source")
  print_array(arr, n)
  new_arr, new_n = form_array(arr, n)

  print("Result which show that programm not working")
  print_array(new_arr, new_n)

if __name__ == '__main__':
  main()
