#!/usr/local/bin/python

import numpy as np
import scipy as sp

class NMF:
  def __init__(self, K=10, max_iter=50, epsilon=0.01):
    self.K=K
    self.max_iter = max_iter
    self.epsilon = epsilon

  def factorize(self, X):
    self.__random_init(X.shape[0],X.shape[1])
    print self.T, self.V
    prev_cost = 1000000000000000000000000.0
    for i in range(self.max_iter):
      XVt = X.dot(np.transpose(self.V))
      TVVt= self.T.dot(self.V).dot(np.transpose(self.V))
      self.T = np.multiply(self.T, np.divide(XVt,TVVt))
      TtX = np.transpose(self.T).dot(X)
      TtTV= np.transpose(self.T).dot(self.T).dot(self.V)
      self.V = np.multiply(self.V, np.divide(TtX,TtTV))

      cost = self.__calc_cost(X)
      if i % 10 == 0 :
        print i, cost
      if abs(prev_cost - cost ) < self.epsilon :
        break
      prev_cost = cost
    return (self.T, self.V)

  def __random_init(self,row,col):
    self.T = np.random.rand(row, self.K)
    self.V = np.random.rand(self.K, col)

  def __calc_cost(self,input):
    mat = input - self.T.dot(self.V)
    return np.linalg.norm(mat) 

if __name__ == '__main__':
  nmf1 = NMF(1,50)
  input = np.matrix([[1,2,3],[4,5,6],[7,8,9]])
  weight,feature = nmf1.factorize(input)
  print weight, feature
  print weight * feature
