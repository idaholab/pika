[Mesh]
  type = FileMesh
  file = init_phi_out_0100_mesh.xdr
  dim = 2
[]

[Variables]
  [./u]
  [../]
[]

[AuxVariables]
  [./phi]
  [../]
  [./T]
  [../]
[]

[Functions]
[]

[Kernels]
  [./vapor_diffusion]
    type = Diffusion
    variable = u
  [../]
  [./vapor_time]
    type = TimeDerivative
    variable = u
  [../]
[]

[AuxKernels]
  [./T_aux]
    type = SolutionAux
    variable = T
    solution = init_T
    direct = true
    execute_on = initial
  [../]
  [./phi_aux]
    type = SolutionAux
    variable = phi
    solution = init_phi
    direct = true
    execute_on = initial
  [../]
[]

[Executioner]
  # Preconditioned JFNK (default)
  type = Transient
  solve_type = PJFNK
  petsc_options_iname = '-ksp_gmres_restart -pc_type -pc_hypre_type'
  petsc_options_value = '500 hypre boomeramg'
[]

[Outputs]
  output_initial = true
  exodus = true
  [./xdr]
    type = XDR
    file_base = init_u_out
  [../]
  [./console]
    type = Console
    perf_log = true
    nonlinear_residuals = true
    linear_residuals = true
  [../]
[]

[BCs]
  active = 'vapor_bc'
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
  [./vapor_bc]
    type = DirichletBC
    variable = u
    boundary = '0 1 2 3'
    value = 0
  [../]
[]

[UserObjects]
  [./init_phi]
    type = SolutionUserObject
    system = nl0
    mesh = init_phi_out_0100_mesh.xdr
    nodal_variables = phi
    es = init_phi_out_0100.xdr
  [../]
  [./init_T]
    type = SolutionUserObject
    system = nl0
    mesh = init_T_out_0001_mesh.xdr
    nodal_variables = T
    es = init_T_out_0001.xdr
  [../]
[]

[ICs]
  [./vapor_ic]
    variable = u
    type = ChemicalPotentialIC
    phase_variable = phi
    temperature = T
  [../]
[]

[PikaMaterials]
  phi = phi
  temperature = 263.15
  interface_thickness = 5e-6
[]

