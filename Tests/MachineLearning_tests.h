//
//  MachineLearning_tests.h
//  Core Lib
//
//  Created by Rasmus Anthin on 2022-12-01.
//

#pragma once
#include "../MachineLearning/ann_dense.h"

namespace ml
{

  namespace ann
  {
  
    void unit_tests()
    {
      Neuron n({ 1.1, 1, 0.7, 1, 1 }, 0.5, PhiType::GELU);
      n.set_inputs({ -0.61, 0.75, 2.6, -1.5, -1 });
      std::cout << '\n';
      n.update_forward();
      std::cout << *n.output() << '\n';
      for (int i = 0; i < 12; ++i)
      {
        n.train(0.57f);
        std::cout << i << " : " << *n.output() << '\n';
      }
      n.print();
      
      std::cout << "== Neural Layer ==\n";
      
      NeuralLayer nl { { { 1.1, 1, 0.7, 1, 1 }, { 0.3, 1.2, 3.2, 0.75, 0.1 } }, { 0.5, -0.21 }, PhiType::GELU };
      nl.set_inputs({ -0.61, 0.75, 2.6, -1.5, -1 });
      for (int i = 0; i < 20; ++i)
        nl.train({ 1, 0 });
      nl.print();
      
      NeuralNetwork nn
      {
        {
          // Ni*No = 5x4
          generate_weights(GenWeightsType::Rndn_m1_p1, 5, 4),
          // Ni*No = 4x2
          generate_weights(GenWeightsType::Rndn_m1_p1, 4, 2),
        },
        { // No = 4, 2
          generate_biases(GenWeightsType::Zero, 4),
          generate_biases(GenWeightsType::Zero, 2)
        },
        { PhiType::Leaky_ReLU, PhiType::Tanh }
      };
      
      nn.set_inputs({ -0.61, 0.75, 2.6, -1.5, -1 });
      for (int i = 0; i < 1'000; ++i)
        nn.train({ 1, 0 }, 0.02, 0.5);
      nn.print();
      nn.print_result();
      
      auto smax = softmax(nn.result(), 3);
      auto smin = softmin(nn.result(), 3);
      auto hmax = hardmax(nn.result());
      auto hmin = hardmin(nn.result());
      auto max_idx = argmax(nn.result());
      auto min_idx = argmin(nn.result());
      std::cout << "smax = \n" << str::column_vector(smax, str::BracketType::MatrixStyle);
      std::cout << "smin = \n" << str::column_vector(smin, str::BracketType::MatrixStyle);
      std::cout << "hmax = \n" << str::column_vector(hmax, str::BracketType::MatrixStyle);
      std::cout << "hmin = \n" << str::column_vector(hmin, str::BracketType::MatrixStyle);
      std::cout << "argmax(nn.result()) = " << str::row_vector(max_idx);
      std::cout << "argmin(nn.result()) = " << str::row_vector(min_idx);
      
      
    }
  
  }

}
