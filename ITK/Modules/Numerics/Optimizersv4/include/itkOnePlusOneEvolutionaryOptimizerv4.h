/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#ifndef itkOnePlusOneEvolutionaryOptimizerv4_h
#define itkOnePlusOneEvolutionaryOptimizerv4_h

#include "itkObjectToObjectOptimizerBase.h"
#include "itkRandomVariateGeneratorBase.h"
#include <string>

namespace itk
{
/** \class OnePlusOneEvolutionaryOptimizerv4
 * \brief 1+1 evolutionary strategy optimizer
 *
 * This optimizer searches for the optimal parameters. It changes its search
 * radius and position using the grow factor ,shrink factor, and isotropic
 * probability function (which is a random unit normal variate generator).
 *
 * This optimizer needs a cost function and a random unit normal
 * variate generator.
 * The cost function should return cost with new position in parameter space
 * which will be generated by 1+1 evolutionary strategy.
 * Users should plug-in the random unit normal variate generator using
 * SetNormalVariateGenerator method.
 *
 * The SetEpsilon method is the minimum value for the frobenius_norm of
 * the covariance matrix. If the fnorm is smaller than this value,
 * the optimization process will stop even before it hits the maximum
 * iteration.
 *
 * Another way to stop the optimization process is calling the
 * StopOptimization method. At next iteration after calling it, the
 * optimization process will stop.
 *
 * This optimizing scheme was initially developed and implemented
 * by Martin Styner, Univ. of North Carolina at Chapel Hill, and his
 * colleagues.
 *
 * For more details. refer to the following articles.
 * "Parametric estimate of intensity inhomogeneities applied to MRI"
 * Martin Styner, G. Gerig, Christian Brechbuehler, Gabor Szekely,
 * IEEE TRANSACTIONS ON MEDICAL IMAGING; 19(3), pp. 153-165, 2000,
 * (http://www.cs.unc.edu/~styner/docs/tmi00.pdf)
 *
 * "Evaluation of 2D/3D bias correction with 1+1ES-optimization"
 * Martin Styner, Prof. Dr. G. Gerig (IKT, BIWI, ETH Zuerich), TR-197
 * (http://www.cs.unc.edu/~styner/docs/StynerTR97.pdf)
 *
 * \sa NormalVariateGenerator
 * \ingroup ITKOptimizersv4
 */

template<typename TInternalComputationValueType>
class ITK_TEMPLATE_EXPORT OnePlusOneEvolutionaryOptimizerv4:
  public ObjectToObjectOptimizerBaseTemplate<TInternalComputationValueType>
{
public:
  /** Standard "Self" typedef. */
  typedef OnePlusOneEvolutionaryOptimizerv4                                   Self;
  typedef ObjectToObjectOptimizerBaseTemplate<TInternalComputationValueType>  Superclass;
  typedef SmartPointer< Self >                                                Pointer;
  typedef SmartPointer< const Self >                                          ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(OnePlusOneEvolutionaryOptimizerv4, Superclass);

  /** Type of the Cost Function   */
  typedef  SingleValuedCostFunctionv4   CostFunctionType;
  typedef  CostFunctionType::Pointer    CostFunctionPointer;

  /** Normal random variate generator type. */
  typedef Statistics::RandomVariateGeneratorBase NormalVariateGeneratorType;

  /** Measure type */
  typedef typename Superclass::MeasureType      MeasureType;

  /** Parameters type */
  typedef typename Superclass::ParametersType   ParametersType;

  /** Scales type */
  typedef typename Superclass::ScalesType       ScalesType;

  /** Set/Get maximum iteration limit. */
  itkSetMacro(MaximumIteration, unsigned int);
  itkGetConstReferenceMacro(MaximumIteration, unsigned int);

  /** Set/Get the search radius grow factor in parameter space. */
  itkSetMacro(GrowthFactor, double);
  itkGetConstReferenceMacro(GrowthFactor, double);

  /** Set/Get the search radius shrink factor. */
  itkSetMacro(ShrinkFactor, double);
  itkGetConstReferenceMacro(ShrinkFactor, double);

  /** Set/Get initial search radius in parameter space */
  itkSetMacro(InitialRadius, double);
  itkGetConstReferenceMacro(InitialRadius, double);

  /** Set/Get the minimal size of search radius
   * (frobenius_norm of covariance matrix). */
  itkSetMacro(Epsilon, double);
  itkGetConstReferenceMacro(Epsilon, double);

  /** Get the current Frobenius norm of covariance matrix */
  itkGetConstReferenceMacro(FrobeniusNorm, double);

  void SetNormalVariateGenerator(NormalVariateGeneratorType *generator);

  /** Initializes the optimizer.
   * Before running this optimizer, this function should have been called.
   *
   * initialRadius: search radius in parameter space
   * grow: search radius grow factor
   * shrink: searhc radius shrink factor */
  void Initialize(double initialRadius, double grow = -1, double shrink = -1);

  /** Return Current Value */
  itkGetConstReferenceMacro(CurrentCost, MeasureType);
  virtual const MeasureType & GetValue() const ITK_OVERRIDE;

  /** Return if optimizer has been initialized */
  itkGetConstReferenceMacro(Initialized, bool);

  /** Start optimization.
   * Optimization will stop when it meets either of two termination conditions,
   * the maximum iteration limit or epsilon (minimal search radius)  */
  virtual void StartOptimization(bool doOnlyInitialization = false) ITK_OVERRIDE;

  /** when users call StartOptimization, this value will be set false.
   * By calling StopOptimization, this flag will be set true, and
   * optimization will stop at the next iteration. */
  void StopOptimization()
  { m_Stop = true; }

  itkGetConstReferenceMacro(CatchGetValueException, bool);
  itkSetMacro(CatchGetValueException, bool);

  itkGetConstReferenceMacro(MetricWorstPossibleValue, double);
  itkSetMacro(MetricWorstPossibleValue, double);

  virtual const std::string GetStopConditionDescription() const ITK_OVERRIDE;

protected:
  OnePlusOneEvolutionaryOptimizerv4();
  OnePlusOneEvolutionaryOptimizerv4(const OnePlusOneEvolutionaryOptimizerv4 &);
  virtual ~OnePlusOneEvolutionaryOptimizerv4() ITK_OVERRIDE;
  virtual void PrintSelf(std::ostream & os, Indent indent) const ITK_OVERRIDE;

private:

  /** Smart pointer to the normal random variate generator. */
  NormalVariateGeneratorType::Pointer m_RandomGenerator;

  /** Maximum iteration limit. */
  unsigned int m_MaximumIteration;

  bool   m_CatchGetValueException;
  double m_MetricWorstPossibleValue;

  /** The minimal size of search radius
   * (frobenius_norm of covariance matrix). */
  double m_Epsilon;

  /** Initial search radius in parameter space. */
  double m_InitialRadius;

  /** Search radius growth factor in parameter space. */
  double m_GrowthFactor;

  /** Search radius shrink factor in parameter space, */
  double m_ShrinkFactor;

  /** Flag tells if the optimizer was initialized using Initialize function. */
  bool m_Initialized;

  /** Internal storage for the value type / used as a cache  */
  MeasureType m_CurrentCost;

  /** This is user-settable flag to stop optimization.
   * when users call StartOptimization, this value will be set false.
   * By calling StopOptimization, this flag will be set true, and
   * optimization will stop at the next iteration. */
  bool m_Stop;

  /** Stop description */
  std::ostringstream m_StopConditionDescription;

  /** Cache variable for reporting the Frobenius Norm
   */
  double m_FrobeniusNorm;
}; // end of class
} // end of namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkOnePlusOneEvolutionaryOptimizerv4.hxx"
#endif

#endif
