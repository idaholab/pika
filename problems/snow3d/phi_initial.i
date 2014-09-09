[Mesh]
  type = GeneratedMesh
  dim = 3
  nx = 5
  ny = 5
  nz = 6
  xmin= 0.001
  ymin = 0.001
  zmin = 0.001
  xmax = 0.002
  ymax = 0.002
  zmax = 0.002
  uniform_refine = 5
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
  [./image]
    type = ImageFunction
    file_base = /home/slauae/Documents/data/msu/0930/0930_rr_rec_tra_bin__Tra
    file_type = png
    threshold = 180
    lower_value = -1
    upper_value = 1
    dimensions = '0.005 0.005 0.006'
  [../]
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

[Executioner]
  # Preconditioned JFNK (default)
  type = Transient
  dt = 10
  solve_type = PJFNK
  petsc_options_iname = '-ksp_gmres_restart -pc_type -pc_hypre_type'
  petsc_options_value = '500 hypre boomeramg'
  nl_rel_tol = 1e-07
  nl_abs_tol = 5e-14
  [./TimeStepper]
    type = IterationAdaptiveDT
    dt = 1
    growth_factor = 3
  [../]
[]

[Postprocessors]
  [./num_elems]
    type = NumElems
  [../]
[]

[Outputs]
  output_initial = true
  console = false
  [./console]
    type = Console
    perf_log = true
    nonlinear_residuals = true
    linear_residuals = true
  [../]
  [./exodus]
    output_final = true
    file_base = phi_initial
    type = Exodus
  [../]
[]

[ICs]
  [./phase_ic]
    type = FunctionIC
    function = image
    variable = phi
  [../]
[]

[PikaMaterials]
  temperature = 268.15
  interface_thickness = 1e-5
  phase = phi
  temporal_scaling = 1e-04
[]
