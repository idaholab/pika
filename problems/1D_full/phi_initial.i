[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 2000
  xmax = .005
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

[BCs]
[]

[Executioner]
  # Preconditioned JFNK (default)
  type = Transient
  num_steps = 20
  dt = 10
  solve_type = PJFNK
  petsc_options_iname = '-ksp_gmres_restart -pc_type -pc_hypre_type'
  petsc_options_value = '500 hypre boomeramg'
  nl_rel_tol = 1e-07
  nl_abs_tol = 1e-13
  [./TimeStepper]
    type = IterationAdaptiveDT
    dt = 0.5
  [../]
[]

[Outputs]
  output_initial = true
  exodus = true
  console = false
  [./console]
    type = Console
    perf_log = true
    nonlinear_residuals = true
    linear_residuals = true
  [../]
  [./xdr]
    file_base = phi_initial_1e5
    output_final = true
    type = XDR
    interval = 10
  [../]
[]

[ICs]
  [./phase_ic]
    variable = phi
    type = KaempferAnalyticPhaseIC
    x2 = .002857
    phi_new = -1
    phi_old = 1
    x3 = .00357
    x1 = .002143
    x4 = .004286
  [../]
[]

[PikaMaterials]
  temperature = 263
  interface_thickness = 8e-6
  phase = phi
  interface_kinetic_coefficient = 5.5e5
  capillary_length = 1.3e-9
  temporal_scaling = 1e-04
[]

