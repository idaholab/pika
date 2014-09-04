[Mesh]
  type = FileMesh
<<<<<<< HEAD
  file = phi_initial_1e5_0003_mesh.xdr
=======
  file = phi_initial_0000_mesh.xdr
>>>>>>> snow_small
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
<<<<<<< HEAD
    type = TensorDiffusion
    variable = T
    use_temporal_scaling = true
    coefficient = 1.0
    mobility_tensor = conductivity_tensor
=======
    type = PikaDiffusion
    variable = T
    use_temporal_scaling = true
    property = conductivity
>>>>>>> snow_small
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
<<<<<<< HEAD
    value = 260.4
=======
    value = 270
>>>>>>> snow_small
  [../]
  [./T_cold]
    type = DirichletBC
    variable = T
    boundary = bottom
<<<<<<< HEAD
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
=======
    value = 269
>>>>>>> snow_small
  [../]
[]

[UserObjects]
  [./phi_initial]
    type = SolutionUserObject
    system = aux0
<<<<<<< HEAD
    mesh = phi_initial_1e5_0003_mesh.xdr
    nodal_variables = phi_aux
    es = phi_initial_1e5_0003.xdr
=======
    mesh = phi_initial_0001_mesh.xdr
    nodal_variables = phi_aux
    es = phi_initial_0001.xdr
    system_variables = phi_aux
>>>>>>> snow_small
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
<<<<<<< HEAD
  temperature = T
  interface_thickness = 1e-5
  condensation_coefficient = .001
  phase = phi
=======
  phi = phi
  temperature = 263.15
  interface_thickness = 5e-6
>>>>>>> snow_small
[]

