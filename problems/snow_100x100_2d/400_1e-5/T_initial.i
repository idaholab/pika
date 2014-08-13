[Mesh]
  type = FileMesh
  file = phi_initial_0003_mesh.xdr
  dim = 2
[]

[Variables]
  [./T]
  [../]
[]

[AuxVariables]
  [./u]
  [../]
  [./phi]
  [../]
[]

[Kernels]
  [./heat_diffusion]
    type = PikaDiffusion
    variable = T
    use_temporal_scaling = true
    property = conductivity
  [../]
[]

[AuxKernels]
  [./phi_aux_kernel]
    type = SolutionAux
    variable = phi
    execute_on = initial
    solution = phi_initial
  [../]
[]

[BCs]
  [./T_hot]
    type = DirichletBC
    variable = T
    boundary = top
    value = 260.8
  [../]
  [./T_cold]
    type = DirichletBC
    variable = T
    boundary = bottom
    value = 260
  [../]
[]

[Materials]
  [./conductivity_tensor]
    type = TensorMobilityMaterial
    block = 0
    phi = phi
    M_1_value = 2.29
    M_2_value = 0.02
    coefficient_name = conductivity_tensor
  [../]
[]

[UserObjects]
  [./phi_initial]
    type = SolutionUserObject
    system = aux0
    mesh = phi_initial_0003_mesh.xdr
    nodal_variables = phi_aux
    es = phi_initial_0003.xdr
  [../]
[]

[Executioner]
  # Preconditioned JFNK (default)
  type = Steady
  solve_type = PJFNK
  petsc_options_iname = '-ksp_gmres_restart -pc_type -pc_hypre_type'
  petsc_options_value = '500 hypre boomeramg'
[]

[Outputs]
  exodus = true
  console = false
  [./console]
    type = Console
    perf_log = true
    nonlinear_residuals = true
    linear_residuals = true
  [../]
  [./xdr]
    file_base = T_initial
    output_final = true
    type = XDR
  [../]
[]

[PikaMaterials]
  temperature = T
  interface_thickness = 1e-5
  condensation_coefficient = .001
  phase = phi
[]

