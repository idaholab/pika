[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 5
  ny = 5
  xmax = 0.01
  ymax = 0.01
  uniform_refine = 2
  elem_type = QUAD4
[]

[Variables]
  [./u]
    order = FIRST
    family = LAGRANGE
  [../]
[]

[AuxVariables]
  active = 'abs_error u_exact'
  [./phi]
  [../]
  [./abs_error]
  [../]
  [./u_exact]
  [../]
[]

[Functions]
  [./u_func]
    type = ParsedFunction
    vars = a
    vals = 100
    value = t*y*sin(a*pi*x)
  [../]
  [./phi_func]
    type = ParsedFunction
    value = t*x*y
  [../]
  [./forcing_func]
    type = ParsedFunction
    vars = a
    vals = 100
    value = y*sin(a*pi*x)+a*a*t*y*sin(a*pi*x)*pi*pi
  [../]
[]

[Kernels]
  # [./u_time]
  # type = TimeDerivative
  # variable = u
  # [../]
  # [./mms]
  # type = MassTransportSourceMMS
  # variable = u
  # phi = phi
  # use_dphi_dt = false
  # [../]
  [./u_diff]
    # D_name = diffusion_coefficient
    type = Diffusion
    variable = u
    block = 0
  [../]
  [./mms]
    type = UserForcingFunction
    variable = u
    function = forcing_func
  [../]
  [./u_time]
    type = TimeDerivative
    variable = u
  [../]
[]

[AuxKernels]
  active = 'u_exact abs_err'
  [./phi_kernel]
    type = FunctionAux
    variable = phi
    function = phi_func
  [../]
  [./u_exact]
    type = FunctionAux
    variable = u_exact
    function = u_func
  [../]
  [./abs_err]
    type = ErrorFunctionAux
    variable = abs_error
    function = u_func
    solution_variable = u
  [../]
[]

[BCs]
  [./all]
    type = FunctionDirichletBC
    variable = u
    boundary = 'bottom left right top'
    function = u_func
  [../]
[]

[PikaMaterials]
  phi = -1
  temperature = 273.15
  diffusion_coefficient = 1
[]

[Postprocessors]
  [./L2_error]
    type = ElementL2Error
    variable = u
    function = u_func
  [../]
  [./ndofs]
    type = NumDOFs
  [../]
  [./hmax]
    type = AverageElementSize
    variable = u
  [../]
[]

[Executioner]
  type = Transient
  num_steps = 10
  dt = 0.01
[]

[Outputs]
  output_initial = true
  exodus = true
  csv = true
[]

[ICs]
  active = 'u_ic'
  [./u_ic]
    function = u_func
    variable = u
    type = FunctionIC
  [../]
  [./phi_ic]
    function = phi_func
    variable = phi
    type = FunctionIC
  [../]
[]

