                   # NC Project 2021

# Group Members are:
# Sonu kumar (19k-0169)
# Sumeet kumar(19k-0171)
# Aman Soofi (19k-1491)
# section: J

# Chapter wise methods:

                  # chapter 2
# 1: Bisection Method:
# 2: Fasle Position:
# 3: Secent Method:

                   # chapter 3
# 4: Legrange Method:
# 5: Newton Forward Difference:
# 6: Newton Backward Difference:

                   # chapter 4
# 7: Three Point End Point Formula:
# 8: Three Point Mid Point Formula:
# 9: Five Point End Point Formula:
# 10: Five Point Mid Point Formula:
# 11: Composite Simpson Rule:

                   # chapter 5
# 12: Modified Euler Method:
# 13: Midpoint Method:
# 14: Heuns Method:


# code starts

import math
from sympy import *

def function():
    equation = input()
    equation = equation.replace("^","**")

    if 'ln' in equation or 'log' in equation or 'e' in equation:
        equation = equation.replace("ln","math.log2")
        equation = equation.replace("log","math.log10")
        equation = equation.replace("e", "math.exp(1)")

    if 'asin' in equation or 'acos' in equation or 'atan' in equation or 'asec' in equation or 'acosec' in equation or 'acot' in equation:
        equation = equation.replace("asin","nisa")
        equation = equation.replace("acos", "soca")
        equation = equation.replace("atan", "nata")
        equation = equation.replace("asec", "cesa")
        equation = equation.replace("acosec", "cesoca")
        equation = equation.replace("acot", "toca")


    if ('sin' in equation or 'cos' in equation or 'tan' in equation or 'sec' in equation or 'cosec' in equation or 'cot' in equation):
        equation = equation.replace("sin","math.sin")
        equation = equation.replace("cos","math.cos")
        equation = equation.replace("tan","math.tan")
        equation = equation.replace("sec","math.sec")
        equation = equation.replace("cosec","math.cosec")
        equation = equation.replace("cot","math.cot")

    if ('nisa' in equation or 'soca' in equation or 'nata' in equation or 'cesa' in equation or 'cesoca' in equation or 'toca' in equation):
        equation = equation.replace("nisa","math.asin")
        equation = equation.replace("soca","math.acos")
        equation = equation.replace("nata","math.atan")
        equation = equation.replace("cesa","math.asec")
        equation = equation.replace("cesoca","math.acosec")
        equation = equation.replace("toca","math.acot")

    return  equation

def f_x(equation,x):
    return eval(equation)


def bisection_method(equation,a,b,epslon,n_decimals):
    x = f_x(equation,x = a)
    y = f_x(equation,x = b)
    error = float(1111111) # larger value
    func_c = 0 # for calculating error for the 1st time

    if x*y < 0:
        while error > epslon:
            c = float((a + b) / 2)
            previous = func_c # to know the previous value
            func_c = f_x(equation, c)

            if previous != 0:
                error = float(func_c - previous)
                if error < 0:
                    error = error - (2*error)
            else:
                error = '-'
            a = round(a,n_decimals)
            b = round(b,n_decimals)
            c = round(c,n_decimals)
            func_c = round(func_c,n_decimals)
            #error = round(error,n_decimals)
            print(f'a = {a}  b = {b}  c = {c}  f(c) = {func_c}  error = {error}')
            error = float(func_c) # for first time value
            if error < 0:
                error = error - (2 * error)

            if (func_c > 0 and  f_x(equation,x = a) > 0) or (func_c < 0 and f_x(equation,x = a) < 0):
                a = c
            if (func_c > 0 and f_x(equation,x = b) > 0) or (func_c < 0 and f_x(equation,x = b) < 0):
                b = c

def fasle_position(equation,a,b,epslon,n_decimals):
    x = f_x(equation, x=a)
    y = f_x(equation, x=b)
    error = float(1111111)  # larger value
    func_c = 0

    if x * y < 0:
        while error > epslon:
            c = (a * f_x(equation, x=b)) - (b * f_x(equation, x=a))
            c = float(c / (f_x(equation, x=b) - f_x(equation, x=a)))
            previous = func_c
            func_c = f_x(equation, c)

            if previous != 0:
                error = float(func_c - previous)
                if error < 0:
                    error = error - (2 * error)
            else:
                error = '-'
            a = round(a, n_decimals)
            b = round(b, n_decimals)
            c = round(c, n_decimals)
            func_c = round(func_c, n_decimals)
            print(f'a = {a}  b = {b}  c = {c}  f(c) = {func_c}  error = {error}')
            error = float(func_c)  # for first time value
            if error < 0:
                error = error - (2 * error)

            if (func_c > 0 and f_x(equation, x=a) > 0) or (func_c < 0 and f_x(equation, x=a) < 0):
                a = c
            if (func_c > 0 and f_x(equation, x=b) > 0) or (func_c < 0 and f_x(equation, x=b) < 0):
                b = c


def secent_method(equation,a,b,epslon,n_decimals):
    error = float(1111111) # larger value
    while error > epslon:
        c = float((b - a) / (f_x(equation, x=b) - f_x(equation, x=a)))
        c = float(f_x(equation, x=b) * c)
        c = float(b - c)
        func_c = f_x(equation, c)
        error = float(c-b)
        if error < 0: # to make valule absolute
            error = error - (2 * error)
        a = round(a, n_decimals)
        b = round(b, n_decimals)
        c = round(c, n_decimals)
        func_c = round(func_c, n_decimals)
        error = round(error, n_decimals)
        print(f' Xn-1 = {a}  Xn = {b}  Xn+1 = {c}  f(Xn+1) = {func_c}  Xn+1 - Xn = {error}')
        a = b
        b = c


def legrange_method(equation):
    f_points = []  # list of float values holding the value of x0 x1 ...etc
    f = []  # list of float values holding the function value of f(x0) f(x1) ...etc
    n = int(input("Enter a degree of polynomial you want to find: "))
    for i in range(n):
         f_points.append(float(input(f'Enter x{i}: ')))
         f.append(f_x(equation, x=f_points[i]))

    x = float(input("Enter the value of X:"))
    l_value = []
    temp = 1
    total_value = 0
    for i in range(n):
        for j in range(n):
            if j != i:
                temp *= float(( x-f_points[j])/(f_points[i] - f_points[j]))
        l_value.append(temp)
        temp = 1

    for i in range(n):
        total_value += l_value[i]*f[i]

    total_value = round(total_value,5)
    print('\n')
    print(f'f({x}) = {total_value}')

def calc_p_forward(p,i):
    if i > 1:
        temp = 1
        for j in range(1,i):
            temp = temp * (p - j)

        return temp*p

    return p

def calc_p_backward(p,i):
    if i > 1:
        temp = 1
        for j in range(1,i):
            temp = temp * (p + j)

        return temp*p

    return p
def fact_number(i):
    if i == 1:
        return 1

    fact = 1
    for j in range(1,i+1):
        fact = fact * j

    return fact

def newton_forward_difference(equation):
    f_points = []  # list of float values holding the value of x0 x1 ...etc
    f = []  # list of float values holding the function value of f(x0) f(x1) ...etc
    n = int(input("Enter a degree of polynomial you want to find: "))
    y = [[0 for i in range(n)]for j in range(n)]  # list of float values of 1st order 2nd order..........
    for i in range(n):
         f_points.append(float(input(f'Enter x{i}: ')))
         f.append(f_x(equation, x=f_points[i]))

    x = float(input("Enter the value of X:"))
    h = f_points[1] - f_points[0]
    p = ((x - f_points[0])/h)
    p = round(p,4)
    size = 0
    for i in range(n):
         y[i][size] = f[i]

    for j in range(1,n):
        for i in range(n - j):
            y[i][j] = y[i+1][j-1] - y[i][j-1]

    print("\n")
    for i in range(0,n):
        print(f_points[i], end="\t");
        for j in range(0,n - i):
            print(y[i][j], end="\t");
        print("")

    sum = y[0][0]
    for i in range(1,n):
        sum = sum + ((calc_p_forward(p,i) * y[0][i]) / fact_number(i))

    sum = round(sum,5)
    print('\n')
    print(f'f({x}) = {sum}')

def newton_backward_difference(equation):
    f_points = []  # list of float values holding the value of x0 x1 ...etc
    f = []  # list of float values holding the function value of f(x0) f(x1) ...etc
    n = int(input("Enter a degree of polynomial you want to find: "))
    y = [[0 for i in range(n)]for j in range(n)]  # list of float values of 1st order 2nd order..........
    for i in range(n):
         f_points.append(float(input(f'Enter x{i}: ')))
         f.append(f_x(equation, x=f_points[i]))

    x = float(input("Enter the value of X:"))
    h = f_points[1] - f_points[0]
    p = ((x - f_points[0])/h)
    p = round(p,4)
    size = 0
    for i in range(n):
         y[i][size] = f[i]

    for j in range(1,n):
        for i in range(n - j):
            y[i][j] = y[i+1][j-1] - y[i][j-1]

    for i in range(0,n):
        print(f_points[i], end="\t");
        for j in range(0,n - i):
            print(y[i][j], end="\t");
        print("")

    sum = y[n-1][0]
    i = n-2
    j = 1
    while i>=0:
        sum = sum + ((calc_p_backward(p,j) * y[i][j]) / fact_number(j))
        j = j + 1
        i = i - 1

    sum = round(sum,5)
    print('\n')
    print(f'f({x}) = {sum}')


def three_point_endPoint_formula(equation):
    f_points = []  # list of float values holding the value of x0 x1 ...etc
    f = []  # list of float values holding the function value of f(x0) f(x1) ...etc
    n = int(input("Enter a degree of polynomial you want to find: "))
    for i in range(n):
        f_points.append(float(input(f'Enter x{i}: ')))
        f.append(f_x(equation, x=f_points[i]))

    x = float(input("Enter the value of X:"))
    h = f_points[1] - f_points[0]
    h = round(h, 4)
    for i in range(n):
        x = f[f_points[i]+h]
        y = f[f_points[i]+(2*h)]
        f_deriative_x = ((-3 * f_points[i]) + (4 * x) - y)
        f_deriative_x = f_deriative_x * (1/(2*h))
        print(f"f(x) = {f[i]}   f(x[i]+h) = {x}    f(x[i]+2h) = {y}    f'(x) = {f_deriative_x}")

def three_point_midPoint_formula(equation):
    f_points = []  # list of float values holding the value of x0 x1 ...etc
    f = []  # list of float values holding the function value of f(x0) f(x1) ...etc
    n = int(input("Enter a degree of polynomial you want to find: "))
    for i in range(n):
        f_points.append(float(input(f'Enter x{i}: ')))
        f.append(f_x(equation, x=f_points[i]))

    x = float(input("Enter the value of X:"))
    h = f_points[1] - f_points[0]
    h = round(h, 4)
    for i in range(n):
        x = f[f_points[i]+h]
        y = f[f_points[i]-h]
        f_deriative_x = (x-y)
        f_deriative_x = f_deriative_x * (1/(2*h))
        print(f"f(x) = {f[i]}   f(x[i]+h) = {x}    f(x[i]-2h) = {y}    f'(x) = {f_deriative_x}")

def five_point_endPoint_formula(equation):
    f_points = []  # list of float values holding the value of x0 x1 ...etc
    f = []  # list of float values holding the function value of f(x0) f(x1) ...etc
    n = int(input("Enter a degree of polynomial you want to find: "))
    for i in range(n):
        f_points.append(float(input(f'Enter x{i}: ')))
        f.append(f_x(equation, x=f_points[i]))

    x = float(input("Enter the value of X:"))
    h = f_points[1] - f_points[0]
    h = round(h, 4)
    for i in range(n):
        w = f[f_points[i]+h]
        x = f[f_points[i]+(2*h)]
        y = f[f_points[i]+(3*h)]
        z = f[f_points[i]+(4*h)]
        f_deriative_x = ((-25 * f[i]) + (48 * w) - (36 * x) + (16 * y) - (3 * z))
        f_deriative_x = f_deriative_x * (1/(2*h))
        print(f"f(x) = {f[i]}   f(x[i]+h) = {w}    f(x[i]+2h) = {x}     f(x[i]+3h) = {y}     f(x[i]+4h) = {z}  f'(x) = {f_deriative_x}")


def five_point_midPoint_formula(equation):
    f_points = []  # list of float values holding the value of x0 x1 ...etc
    f = []  # list of float values holding the function value of f(x0) f(x1) ...etc
    n = int(input("Enter a degree of polynomial you want to find: "))
    for i in range(n):
        f_points.append(float(input(f'Enter x{i}: ')))
        f.append(f_x(equation, x=f_points[i]))

    x = float(input("Enter the value of X:"))
    h = f_points[1] - f_points[0]
    h = round(h, 4)
    for i in range(n):
        u = f[f_points[i] - (2*h)]
        v = f[f_points[i]-h]
        w = f[f_points[i]+h]
        x = f[f_points[i]+(2*h)]
        f_deriative_x = (u - (8 * v) + (8 * w) - x)
        f_deriative_x = f_deriative_x * (1/(2*h))
        print(f"f(x) = {f[i]}   f(x[i]- 2h) = {u}    f(x[i]-h) = {v}     f(x[i]+h) = {w}     f(x[i]+2h) = {x}  f'(x) = {f_deriative_x}")

def composite_simpson_rule(equation):
    f_points = []  # list of float values holding the value of x0 x1 ...etc
    f = []  # list of float values holding the function value of f(x0) f(x1) ...etc
    n = int(input("Enter the value of n: "))
    a = float(input("Enter the value of lower limit (a): "))
    b = float(input("Enter the value of upper limit (b): "))
    h = float(b-a)
    h = float(h/n)
    for i in range(n+1):
        f_points.append(a + (i * h))
        f.append(f_x(equation, x=f_points[i]))

    sum = 0.0
    for i in range(int(n/2) - 1):
        sum = sum + (2 * f[2 * (i+1)])

    for i in range(int(n/2)):
        sum = sum + (4 * f[2*(i+1) - 1])


    sum = sum + f[0]+f[n]
    sum = sum * (h/3)
    sum = round(sum,5)
    print(sum)


def eval_function(t,y,equation):
    return eval(equation)

def modified_euler_method(equation):
    f_points = []  # list of float values holding the value of x0 x1 ...etc
    n = int(input("Enter the value of n: "))
    f = [0 for i in range(n+1)]  # list of float values holding the function value of f(x0) f(x1) ...etc
    a = float(input("Enter the value of lower limit (a): "))
    b = float(input("Enter the value of upper limit (b): "))
    h = float(b - a)
    h = float(h / n)
    for i in range(n + 1):
        f_points.append(a + (i * h))

    f[0] = float(input(f'Enter the initial_value at Y({a}) = '))

    for i in range(n):
        k1 = h * eval_function(f_points[i],f[i],equation)
        k2 = h * eval_function(f_points[i+1],(f[i] + k1),equation)
        f[i+1] = f[i] + ((1/2) * (k1+k2))

    for i in range(n+1):
        print(f" ti = {f_points[i]}     f(ti) = {f[i]}")



def midpoint_method(equation):
    f_points = []  # list of float values holding the value of x0 x1 ...etc
    n = int(input("Enter the value of n: "))
    f = [0 for i in range(n+1)]  # list of float values holding the function value of f(x0) f(x1) ...etc
    a = float(input("Enter the value of lower limit (a): "))
    b = float(input("Enter the value of upper limit (b): "))
    h = float(b - a)
    h = float(h / n)
    for i in range(n + 1):
        f_points.append(a + (i * h))

    f[0] = float(input(f'Enter the initial_value at Y({a}) = '))

    for i in range(n):
        k1 = eval_function(f_points[i],f[i],equation)
        k2 = eval_function(f_points[i] + (h/2),f[i] + ((h/2) * k1),equation)
        f[i+1] = f[i] + (h * k2)

    for i in range(n+1):
        print(f" ti = {f_points[i]}     f(ti) = {f[i]}")


def Heuns_method(equation):
    f_points = []  # list of float values holding the value of x0 x1 ...etc
    n = int(input("Enter the value of n: "))
    f = [0 for i in range(n+1)]  # list of float values holding the function value of f(x0) f(x1) ...etc
    a = float(input("Enter the value of lower limit (a): "))
    b = float(input("Enter the value of upper limit (b): "))
    h = float(b - a)
    h = float(h / n)
    for i in range(n + 1):
        f_points.append(a + (i * h))

    f[0] = float(input(f'Enter the initial_value at Y({a}) = '))

    for i in range(n):
        k1 = eval_function(f_points[i],f[i],equation)
        k2 = eval_function(f_points[i] + (h/3),f[i] + ((h/3) * k1),equation)
        k3 = eval_function(f_points[i] + ((2 * h)/3),f[i] + (((2 * h)/3) * k2),equation)
        f[i+1] = f[i] + ((h/4) * (k1 + (3 * k3)))

    for i in range(n+1):
        print(f" ti = {f_points[i]}     f(ti) = {f[i]}")





print("\n\n\t\t\t\t\t\t\t*****************************NUMERICAL COMPUTING*****************************\n\n")
print(" 1: Bisection Method: ")
print(" 2: Fasle Position: ")
print(" 3: Secent Method: ")
print(" 4: Legrange Method: ")
print(" 5: Newton Forward Difference: ")
print(" 6: Newton Backward Difference: ")
print(" 7: Three Point End Point Formula: ")
print(" 8: Three Point Mid Point Formula: ")
print(" 9: Five Point End Point Formula: ")
print("10: Five Point Mid Point Formula: ")
print("11: Composite Simpson Rule: ")
print("12: Modified Euler Method: ")
print("13: Midpoint Method: ")
print("14: Heuns Method: ")
print("0: Exit")

while true:
    choice = int(input(f'Enter your choice: '))
    if choice == 0:
        break
    elif choice > 14:
        print("Wrong choice !!!!!\n")
        continue


    if choice > 0 and choice < 12:
        print("f(x) = ",end=" ")
    elif choice > 11 and choice < 15:
        print("f(t,y) = ", end=" ")
    equ = function()

    # chapter 2
    if choice < 4 and choice > 0:
        print("Enter value of a: ")
        a = float(input())
        print("Enter value of b: ")
        b = float(input())
        print("Enter Tolrence value: ")
        epslon = float(input())
        print("Enter number of decimals you want: ")
        n_decimals  = int(input())
        if choice == 1:
            bisection_method(equ,a,b,epslon,n_decimals)
        elif choice == 2:
            fasle_position(equ,a,b,epslon,n_decimals)
        else:
             secent_method(equ,a,b,epslon,n_decimals)

    # chapter 3
    elif choice > 3 and choice < 7:
        if choice == 4:
            legrange_method(equ)
        elif choice == 5:
            newton_forward_difference(equ)
        else:
            newton_backward_difference(equ)

    # chapter 4
    elif choice > 6 and choice < 12:
        if choice == 7:
            three_point_endPoint_formula(equ)
        elif choice == 8:
            three_point_midPoint_formula(equ)
        elif choice == 9:
            five_point_endPoint_formula(equ)
        elif choice == 10:
            five_point_midPoint_formula(equ)
        else:
            composite_simpson_rule(equ)

    # chapter 5
    elif choice > 11 and choice < 15:
        if choice == 12:
            modified_euler_method(equ)
        elif choice == 13:
            midpoint_method(equ)
        else:
            Heuns_method(equ)
    print("\n")
























