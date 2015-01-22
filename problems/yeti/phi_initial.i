[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 6
  ny = 6
  xmax = .005
  ymax = .005
  uniform_refine = 6
[]

[MeshModifiers]
[]

[Variables]
  [./phi]
  [../]
[]

[AuxVariables]
  [./u]
  [../]
  [./phi_aux]
  [../]
[]

[Functions]
  [./snow_ct]
    type = ImageFunction
    upper_value = -1
    lower_value = 1
    file = input.png
    threshold = 128
  [../]
[]

[Kernels]
  [./phase_time]
    type = PikaTimeDerivative
    variable = phi
    property = relaxation_time
  [../]
  [./phase_diffusion]
    type = PikaDiffusion
    variable = phi
    property = interface_thickness_squared
  [../]
  [./phase_double_well]
    type = DoubleWellPotential
    variable = phi
    mob_name = mobility
  [../]
[]

[AuxKernels]
  [./phi_aux]
    type = PikaPhaseInitializeAux
    variable = phi_aux
    phase = phi
  [../]
[]

#[BCs]
#  [./Periodic]
#    [./phi_periodic]
#      variable = phi
#      auto_direction = y
#    [../]
#  [../]
#[]

[Executioner]
  # Preconditioned JFNK (default)
  type = Transient
  num_steps = 20
  dt = 10
  solve_type = PJFNK
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
  nl_rel_tol = 1e-04
  nl_abs_tol = 1e-12
  l_tol = 1e-4
  [./TimeStepper]
    type = IterationAdaptiveDT
    dt = 0.5
  [../]
[]

[Outputs]
  output_initial = true
  exodus = true
  file_base = phi_initial_out
  print_linear_residuals = true
  print_perf_log = true
[]

[ICs]
  [./phase_ic]
    variable = phi
    type = FunctionIC
    function = snow_ct
  [../]
[]

[PikaMaterials]
  temperature = 263.15
  phase = phi
  interface_thickness = 5e-5
  temporal_scaling = 1e-4
  condensation_coefficient = .004
[]
