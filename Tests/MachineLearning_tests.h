//
//  MachineLearning_tests.h
//  Core Lib
//
//  Created by Rasmus Anthin on 2022-12-01.
//

#pragma once
#include "../MachineLearning/MachineLearning.h"

namespace ml
{

  namespace ann
  {
  
    void unit_tests()
    {
      ml::ann::Neuron n({ 1.1, 1, 0.7, 1, 1 }, 0.5, ml::ann::PhiType::GELU);
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
      
      ml::ann::NeuralLayer nl { { { 1.1, 1, 0.7, 1, 1 }, { 0.3, 1.2, 3.2, 0.75, 0.1 } }, { 0.5, -0.21 }, ml::ann::PhiType::GELU };
      nl.set_inputs({ -0.61, 0.75, 2.6, -1.5, -1 });
      for (int i = 0; i < 20; ++i)
        nl.train({ 1, 0 });
      nl.print();
      
      ml::ann::NeuralNetwork nn
      {
        {
          // Ni*No = 5x4
          ml::ann::generate_weights(ml::ann::GenWeightsType::Rndn_m1_p1, 5, 4),
          // Ni*No = 4x2
          ml::ann::generate_weights(ml::ann::GenWeightsType::Rndn_m1_p1, 4, 2),
        },
        { // No = 4, 2
          generate_biases(ml::ann::GenWeightsType::Zero, 4),
          generate_biases(ml::ann::GenWeightsType::Zero, 2)
        },
        { ml::ann::PhiType::Leaky_ReLU, ml::ann::PhiType::Tanh }
      };
      
      nn.set_inputs({ -0.61, 0.75, 2.6, -1.5, -1 });
      for (int i = 0; i < 1'000; ++i)
        nn.train({ 1, 0 }, 0.02, 0.5);
      nn.print();
      nn.print_output();

    }
  
  }

}
