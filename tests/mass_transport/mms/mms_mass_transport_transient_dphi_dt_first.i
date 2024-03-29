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
  [./phi]
  [../]
  [./u_diff]
  [../]
[]

[Functions]
  [./u_func]
    type = ParsedFunction
    vars = a
    vals = 100
    value = t*y*sin(a*pi*x)
  [../]
  [./forcing_func]
    type = ParsedFunction
    vars = 'a Dv'
    vals = '100 0.00002178'
    value = y*sin(a*pi*x)+a*a*Dv*t*t*y*cos(a*pi*x)*pi+a*a*Dv*(-a*t*x+1)*t*y*sin(a*pi*x)*pi*pi-100*x
  [../]
  [./phi_func]
    type = ParsedFunction
    value = 200*t*x-1
  [../]
[]

[Kernels]
  [./u_diff]
    type = MatDiffusion
    variable = u
    block = 0
    D_name = diffusion_coefficient
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
  [./u_phi_time]
    type = PikaCoupledTimeDerivative
    variable = u
    coupled_variable = phi
    coefficient = 0.5
  [../]
[]

[AuxKernels]
  [./phi_aux]
    type = FunctionAux
    variable = phi
    function = phi_func
    execute_on = 'initial linear nonlinear'
  [../]
  [./u_diff_aux]
    type = ErrorFunctionAux
    variable = u_diff
    function = u_func
    solution_variable = u
    execute_on = 'initial linear nonlinear'
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

[Postprocessors]
  [./L2_error]
    type = ElementL2Error
    variable = u
    function = u_func
  [../]
  [./hmax]
    type = AverageElementSize
    execute_on = 'initial timestep_end'
  [../]
  [./L2_norm]
    type = ElementL2Norm
    variable = u
  [../]
[]

[Executioner]
  type = Transient
  num_steps = 5
  dt = 10000
  nl_rel_tol = 1e-12
[]

[Outputs]
  exodus = true
  csv = true
[]

[ICs]
  [./u_ic]
    function = u_func
    variable = u
    type = FunctionIC
  [../]
[]

[PikaMaterials]
  reference_temperature = 263.15
  phase = phi
  temperature = 268.15
  water_vapor_diffusion_coefficient = 0.00002178
[]
