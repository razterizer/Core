//
//  MachineLearning_tests.h
//  Core Lib
//
//  Created by Rasmus Anthin on 2022-12-01.
//

#pragma once
#include "../MachineLearning/ann_dense.h"
#include "../MachineLearning/ann_cnn.h"

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
      auto max_idx = stlutils::argmax(nn.result());
      auto min_idx = stlutils::argmin(nn.result());
      std::cout << "smax = \n" << str::column_vector(smax, str::BracketType::MatrixStyle);
      std::cout << "smin = \n" << str::column_vector(smin, str::BracketType::MatrixStyle);
      std::cout << "hmax = \n" << str::column_vector(hmax, str::BracketType::MatrixStyle);
      std::cout << "hmin = \n" << str::column_vector(hmin, str::BracketType::MatrixStyle);
      std::cout << "argmax(nn.result()) = " << str::row_vector(max_idx);
      std::cout << "argmin(nn.result()) = " << str::row_vector(min_idx);
      
      // CNN
      
      auto x = std::vector<float> { 1, 0, -2, 7, 3, 9, 1 };
      auto p0_1d = pooling_1d(x, PoolingType::Max, 2, 2, false);
      assert((p0_1d == std::vector<float> { 1, 7, 9 }));
      
      auto p1_1d = pooling_1d(x, PoolingType::Max, 2, 2, true);
      assert((p1_1d == std::vector<float> { 1, 7, 9, 1 }));
      
      auto p2_1d = pooling_1d(x, PoolingType::Min, 3, 1, false);
      assert((p2_1d == std::vector<float> { -2, -2, -2, 3, 1 }));
      
      auto p3_1d = pooling_1d(x, PoolingType::Min, 3, 1, true);
      assert((p3_1d == std::vector<float> { -2, -2, -2, 3, 1 }));
      
      auto p4_1d = pooling_1d(x, PoolingType::Mean, 2, 1, false);
      assert((p4_1d == std::vector { 0.5f, -1.f, 2.5f, 5.f, 6.f, 5.f }));
      
      auto af_p4_1d = activation_1d(p4_1d, PhiType::ReLU);
      assert((af_p4_1d == std::vector { 0.5f, 0.f, 2.5f, 5.f, 6.f, 5.f }));
      
      auto kernel = std::vector<float> { 1, 2, 3 };
      auto c0_1d = conv_1d(x, kernel, 1.f, ConvType::Full);
      assert((c0_1d == std::vector<float> { 2, 3, 2, 4, 12, 37, 29, 30, 4 }));
      
      auto f = std::vector<float> { 0, 0, -1, 2, 1, 0, 1, 2, 3, 0, 0 };
      auto g = std::vector<float> { 0, 1, -1, 1, 0 };
      auto c1_1d = conv_1d(f, g, 0, ConvType::Full);
      assert((c1_1d == std::vector<float> { 0, 0, 0, -1, 3, -2, 1, 2, 1, 2, -1, 3, 0, 0, 0 }));
      auto c2_1d = conv_1d(f, g, 0, ConvType::Same);
      assert((c2_1d == std::vector<float> { 0, -1, 3, -2, 1, 2, 1, 2, -1, 3, 0 }));
      auto c3_1d = conv_1d(f, g, 0, ConvType::Valid);
      assert((c3_1d == std::vector<float> { 3, -2, 1, 2, 1, 2, -1 }));
      g = std::vector<float> { 0, 1, 2, 3 };
      auto c4_1d = conv_1d(f, g, 0, ConvType::Full);
      assert((c4_1d == std::vector<float> { 0, 0, 0, -1, 0, 2, 8, 4, 4, 10, 12, 9, 0, 0 }));
      auto c5_1d = conv_1d(f, g, 0, ConvType::Same);
      assert((c5_1d == std::vector<float> { 0, -1, 0, 2, 8, 4, 4, 10, 12, 9, 0 }));
      auto c6_1d = conv_1d(f, g, 0, ConvType::Valid);
      assert((c6_1d == std::vector<float> { -1, 0, 2, 8, 4, 4, 10, 12 }));
      g = std::vector<float> { 1, -1, -2 };
      auto c7_1d = conv_1d(f, g, 0, ConvType::Full);
      assert((c7_1d == std::vector<float> { 0, 0, -1, 3, 1, -5, -1, 1, -1, -7, -6, 0, 0 }));
      auto c8_1d = conv_1d(f, g, 0, ConvType::Same);
      assert((c8_1d == std::vector<float> { 0, -1, 3, 1, -5, -1, 1, -1, -7, -6, 0 }));
      auto c9_1d = conv_1d(f, g, 0, ConvType::Valid);
      assert((c9_1d == std::vector<float> { -1, 3, 1, -5, -1, 1, -1, -7, -6 }));
      g = std::vector<float> { -1, 5 };
      auto c10_1d = conv_1d(f, g, 0, ConvType::Full);
      assert((c10_1d == std::vector<float> { 0, 0, 1, -7, 9, 5, -1, 3, 7, 15, 0, 0 }));
      auto c11_1d = conv_1d(f, g, 0, ConvType::Same);
      assert((c11_1d == std::vector<float> { 0, 1, -7, 9, 5, -1, 3, 7, 15, 0, 0 }));
      auto c12_1d = conv_1d(f, g, 0, ConvType::Valid);
      assert((c12_1d == std::vector<float> { 0, 1, -7, 9, 5, -1, 3, 7, 15, 0 }));
      g = std::vector<float> { 4 };
      auto c13_1d = conv_1d(f, g, 0, ConvType::Full);
      assert((c13_1d == std::vector<float> { 0, 0, -4, 8, 4, 0, 4, 8, 12, 0, 0 }));
      auto c14_1d = conv_1d(f, g, 0, ConvType::Same);
      assert((c14_1d == std::vector<float> { 0, 0, -4, 8, 4, 0, 4, 8, 12, 0, 0 }));
      auto c15_1d = conv_1d(f, g, 0, ConvType::Valid);
      assert((c15_1d == std::vector<float> { 0, 0, -4, 8, 4, 0, 4, 8, 12, 0, 0 }));
      f = std::vector<float> { 0, 0, -1, 2, 1, 0, 1, 2, 3, 0, 0, 1 };
      g = std::vector<float> { 0, 1, -1, 1, 0 };
      auto c16_1d = conv_1d(f, g, 0, ConvType::Full);
      assert((c16_1d == std::vector<float> { 0, 0, 0, -1, 3, -2, 1, 2, 1, 2, -1, 3, 1, -1, 1, 0 }));
      auto c17_1d = conv_1d(f, g, 0, ConvType::Same);
      assert((c17_1d == std::vector<float> { 0, -1, 3, -2, 1, 2, 1, 2, -1, 3, 1, -1 }));
      auto c18_1d = conv_1d(f, g, 0, ConvType::Valid);
      assert((c18_1d == std::vector<float> { 3, -2, 1, 2, 1, 2, -1, 3 }));
      g = std::vector<float> { 1, -1 };
      auto c19_1d = conv_1d(f, g, 0, ConvType::Full);
      assert((c19_1d == std::vector<float> { 0, 0, -1, 3, -1, -1, 1, 1, 1, -3, 0, 1, -1 }));
      auto c20_1d = conv_1d(f, g, 0, ConvType::Same);
      assert((c20_1d == std::vector<float> { 0, -1, 3, -1, -1, 1, 1, 1, -3, 0, 1, -1 }));
      auto c21_1d = conv_1d(f, g, 0, ConvType::Valid);
      assert((c21_1d == std::vector<float> { 0, -1, 3, -1, -1, 1, 1, 1, -3, 0, 1 }));
      f = std::vector<float> { -7, 0, -1, 2 };
      g = std::vector<float> { 0, 1, -1, 1, 0 };
      auto c22_1d = conv_1d(f, g, 0, ConvType::Full);
      assert((c22_1d == std::vector<float> { 0, -7, 7, -8, 3, -3, 2, 0 }));
      auto c23_1d = conv_1d(f, g, 0, ConvType::Same);
      assert((c23_1d == std::vector<float> { 7, -8, 3, -3 }));
      auto c24_1d = conv_1d(f, g, 0, ConvType::Valid);
      assert((c24_1d == std::vector<float> {}));
      f = std::vector<float> { -7, 0, -1 };
      auto c25_1d = conv_1d(f, g, 0, ConvType::Full);
      assert((c25_1d == std::vector<float> { 0, -7, 7, -8, 1, -1, 0 }));
      auto c26_1d = conv_1d(f, g, 0, ConvType::Same);
      assert((c26_1d == std::vector<float> { 7, -8, 1 }));
      auto c27_1d = conv_1d(f, g, 0, ConvType::Valid);
      assert((c27_1d == std::vector<float> {}));
    }
  
  }

}
