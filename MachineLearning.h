//
//  MachineLearning.h
//  Core Lib
//
//  Created by Rasmus Anthin on 2022-11-28.
//

#pragma once
#include "StlUtils.h"
#include <optional>

namespace ml
{

  namespace ann
  {
  
    enum class PhiType
    {
      BinaryStep,
      Heaviside_BinaryStep,
      Linear,
      Sigmoid,
      Tanh,
      ReLU,
      Leaky_ReLU,
      Parametric_ReLU,
      ELU,
      Swish,
      GELU,
      SELU,
    };
  
    float phi(float z, PhiType type, float a = 1.f, float l = 1.1f)
    {
      switch (type)
      {
        case PhiType::BinaryStep: return z < 0 ? 0 : 1;
        case PhiType::Heaviside_BinaryStep: return z <= 0 ? 0 : 1;
        case PhiType::Linear: return z;
        case PhiType::Sigmoid: return 1./(1 + std::exp(-z));
        case PhiType::Tanh: return std::tanh(z);
        case PhiType::ReLU: return std::max(0.f, z);
        case PhiType::Leaky_ReLU: return std::max(0.1f*z, z);
        case PhiType::Parametric_ReLU: return std::max(a*z, z);
        case PhiType::ELU: return z < 0 ? a*(std::exp(z) - 1) : z;
        case PhiType::Swish: return z*phi(z, PhiType::Sigmoid);
        case PhiType::GELU: return 0.5*z*(1 + std::tanh(M_2_SQRTPI*M_SQRT1_2*(z + 0.044715*math::cube(z))));
        case PhiType::SELU: return l*phi(z, PhiType::ELU, a, l);
      }
    }
  
    float phi_diff(float z, PhiType type, float a = 1.f, float l = 1.1f)
    {
      switch (type)
      {
        case PhiType::BinaryStep: return 0.f; // Actually inf at 0- and 0 everywhere else.
        case PhiType::Heaviside_BinaryStep: return 0.f; // Actually inf at 0+ and 0 everywhere else.
        case PhiType::Linear: return 1.f;
        case PhiType::Sigmoid:
        {
          auto s = phi(z, type, a, l);
          return s * (1 - s);
        }
        case PhiType::Tanh:
        {
          auto th = phi(z, type, a, l);
          return 1 - math::sq(th);
        }
        case PhiType::ReLU: return z < 0 ? 0 : 1;
        case PhiType::Leaky_ReLU: return z < 0 ? 0.1 : 1;
        case PhiType::Parametric_ReLU: return z < 0 ? a : 1;
        case PhiType::ELU: return z < 0 ? phi(z, type, a, l) + a : 1;
        case PhiType::Swish:
        {
          auto sw = phi(z, type, a, l);
          auto sig = phi(z, PhiType::Sigmoid, a, l);
          return sw + sig * (1 - sw);
        }
        case PhiType::GELU:
        {
          auto z3 = math::cube(z);
          auto sech = [](float v) { return std::sqrt(1 - math::sq(std::tanh(v))); };
          auto b = 0.797885f*z + 0.0356774f*z3;
          return 0.5f + (0.398942f*z + 0.0535161f*z3)*math::sq(sech(b)) + 0.5f*std::tanh(b);
        }
        case PhiType::SELU: return l*phi_diff(z, PhiType::ELU, a, l);
      }
    }
  
    class Input
    {
      float perceptron_signal = 0.f;
      const float* dendrite_output = nullptr;
      bool set = false;
      
    public:
      Input() = default;
      Input(const float signal) : perceptron_signal(signal), set(true) {}
      Input(const float* output) : dendrite_output(output), set(true) {}
      
      std::optional<float> get() const
      {
        if (!set)
          return {};
        if (dendrite_output != nullptr)
          return *dendrite_output;
        return perceptron_signal;
      }
    };
    
    template<size_t Nw>
    class Neuron
    {
      std::array<Input, Nw> inputs;
      std::array<float, Nw> weights;
      float bias = 0.f;
      float z = 0.f;
      PhiType phi_type;
      float phi_param_a = 1.f;
      float phi_param_l = 1.1f;
      float y = 0.f;
      
    public:
      Neuron(const std::array<float, Nw>& w, float b, PhiType af_type)
        : weights(w), bias(b), phi_type(af_type)
      {
      }
      
      void set_inputs(const std::array<Input, Nw>& x)
      {
        inputs = x;
      }
      
      void set_phi_params(float a, float l)
      {
        phi_param_a = a;
        phi_param_l = l;
      }
      
      float update_forward()
      {
        std::vector<float> x, w;
        for (int i = 0; i < Nw; ++i)
        {
          auto ival = inputs[i].get();
          if (ival.has_value())
          {
            x.emplace_back(ival.value());
            w.emplace_back(weights[i]);
          }
        }
        z = stlutils::dot(x, w);
        z += bias;
        y = phi(z, phi_type, phi_param_a, phi_param_l);
        return y;
      }
      
      // Back-prop
      float update_backward()
      {
        
      }
      
      const float* output() const { return &y; }
      
    };
  
  }

}
