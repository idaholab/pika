[Mesh]
  type = FileMesh
  file = init_phi_out_0100_mesh.xdr
  dim = 2
[]

[Variables]
  [./T]
  [../]
[]

[AuxVariables]
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
  [./phi_aux]
    type = SolutionAux
    variable = phi
    solution = init_phi
    direct = true
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
  output_initial = true
  exodus = true
  [./xdr]
    type = XDR
    file_base = init_T_out
  [../]
  [./console]
    type = Console
    perf_log = true
    nonlinear_residuals = true
    linear_residuals = true
  [../]
[]

[BCs]
  [./T_hot]
    type = DirichletBC
    variable = T
    boundary = bottom
    value = 267.15
  [../]
  [./T_cold]
    type = DirichletBC
    variable = T
    boundary = top
    value = 264.15
  [../]
[]

[UserObjects]
  [./init_phi]
    type = SolutionUserObject
    system = nl0
    mesh = init_phi_out_0010_mesh.xdr
    nodal_variables = phi
    es = init_phi_out_0010.xdr
  [../]
[]

[ICs]
  [./temp_ic]
    variable = T
    type = ConstantIC
    value = 264.15
  [../]
[]

[PikaMaterials]
  phi = phi
  temperature = 263.15
  interface_thickness = 5e-6
[]

